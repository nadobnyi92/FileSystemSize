#include "task_queue.h"

void TaskQueue::addTask( std::shared_ptr<Task> task )
{
    m_tasks.push( task );
}

std::shared_ptr<Task> TaskQueue::createTask( const std::filesystem::path& path )
{
    auto ptr = std::make_shared<Task>( path, *this );
    m_tasks.push( ptr );
    return ptr;
}

std::shared_ptr<Task> TaskQueue::getTask()
{
    std::lock_guard< std::mutex > guard{ m_mutex };
    if( m_tasks.empty() )
    {
        return {};
    }
    auto task = m_tasks.front();
    m_tasks.pop();
    return task;
}

