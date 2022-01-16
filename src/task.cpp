#include "task.h"
#include "task_queue.h"
#include "logger.h"

#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

int task_counter;

Task::Task( const std::filesystem::path& path, TaskQueue& queue ) 
    : m_id( ++task_counter ) 
    , m_state( State::READY )
    , m_result( 0 ) 
    , m_path( path )
    , m_queue( queue ) {}
    

int Task::id() const
{
    return m_id;
}

int Task::result() const
{
    return m_result;
}

void Task::print( int deep )
{
    for( const auto& child: m_children )
    {
        child->print( deep + 1 );
    }
}

void Task::process()
{
    State state = State::READY;
    if( m_state.compare_exchange_weak( state, State::ACTIVE ) )
    {
        //recursive loop by children
        if( fs::exists( m_path ) )
        {
            for( const auto & entry : fs::directory_iterator( m_path ) )
            {
                if( fs::is_directory( entry.path() ) )
                {
                    m_children.push_back( m_queue.createTask( entry.path() ) );
                }
                else
                {
                    try
                    {
                        m_result += fs::file_size( entry.path() );
                    }
                    catch(...) ///TODO fix it
                    {

                    }
                }
            }
        }
        if( m_children.empty() )
        {
            std::stringstream ss;
            ss << m_path << " size " << m_result;
            Logger::instance().log( ss.str().c_str() );
            m_state.store( State::DONE );
            return;
        }
        else
        {
            m_state.store( State::WAIT_CHILD );
        }
    }
    state = State::WAIT_CHILD; //TODO only ready
    if( m_state.compare_exchange_weak( state, State::ACTIVE ) )
    {
        auto it = std::partition( m_children.begin(), m_children.end(),
                []( const std::shared_ptr<Task>& task ){ return !task->isDone(); });
        for( auto rem_it = it; rem_it != m_children.end(); ++rem_it )
        {
            m_result += (*rem_it)->result(); 
        }
        m_children.erase( it, m_children.end() );
        if( m_children.empty() )
        {
            std::stringstream ss;
            ss << m_path << " size " << m_result;
            Logger::instance().log( ss.str().c_str() );
            m_state.store( State::DONE );
        }
        else
        {
            m_state.store( State::WAIT_CHILD );
        }
    }
}

void Task::finalize()
{

}

void Task::readyChild()
{
    State state = State::WAIT_CHILD;
    m_state.compare_exchange_weak( state, State::READY_CHILD );
}

bool Task::isDone() const
{
    return m_state == State::DONE;
}

