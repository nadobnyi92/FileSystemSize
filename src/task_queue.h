#pragma once

#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include "task.h"

#include <queue>
#include <memory>
#include <mutex>

class TaskQueue
{
public:
    void addTask( std::shared_ptr<Task> task );
    std::shared_ptr<Task> createTask( const std::filesystem::path& path );
    std::shared_ptr<Task> getTask();

private:
    std::queue< std::shared_ptr<Task> > m_tasks;
    std::mutex m_mutex;
};

#endif //TASK_QUEUE_H
 
