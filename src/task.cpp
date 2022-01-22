#include "task.h"
#include "task_queue.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <map>

namespace fs = std::filesystem;

Task::Task(std::filesystem::path  path, TaskQueue& queue, Task* parent )
    : m_state( State::READY )
    , m_result( 0 ) 
    , m_path( std::move( path ) )
    , m_queue( queue )
    , m_parent( parent ) {}

unsigned long Task::result() const
{
    return m_result;
}

bool Task::process()
{
    State state = State::READY;
    if( m_state.compare_exchange_strong( state, State::ACTIVE ) )
    {
        for( const auto & entry : fs::directory_iterator( m_path ) )
        {
            auto path = entry.path();
            if( fs::is_directory( path ) )
            {
                m_children.push_back( m_queue.createTask( path, this ) );
            }
            else if( fs::is_regular_file( path ) )
            {
                m_result += fs::file_size( path );
            }
        }
        return finish();
    }
    state = State::READY_CHILD;
    if( m_state.compare_exchange_strong( state, State::ACTIVE ) )
    {
        auto it = std::partition( m_children.begin(), m_children.end(),
                []( const std::shared_ptr<Task>& task ){ return !task->isDone(); });
        m_result += std::accumulate(it, m_children.end(), 0,
                        [](int sum, const std::shared_ptr<Task>& task ){ return sum + task->result(); } );
        m_children.erase( it, m_children.end() );
        return finish();
    }
    return false;
}

bool Task::finish()
{
    if( m_children.empty() )
    {
        if( m_parent )
        {
            m_parent->readyChildren();
        }
        else
        {
            std::cout << m_path << " size " << formatedSize() << std::endl;
        }
        m_state.store( State::DONE );
        return true;
    }
    else
    {
        State state = State::ACTIVE;
        m_state.compare_exchange_strong( state, State::WAIT_CHILD );
        return false;
    }
}

std::string Task::formatedSize() const
{
    std::stringstream fmt;
    static const char* suffix[] = { "", "K", "M", "G" };

    unsigned long val = m_result;
    unsigned long mod = 0;
    int idx = 0;

    while( val / 1024 )
    {
        val /= 1024;
        mod = val % 1024;
        ++idx;
    }
    fmt << val << "." << mod << " " << suffix[ idx ];
    return fmt.str();
}

void Task::readyChildren()
{
    m_state.store( State::READY_CHILD );
}

bool Task::isDone() const
{
    return m_state == State::DONE;
}
