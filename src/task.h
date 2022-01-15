#pragma once

#ifndef TASK_H
#define TASK_H

#include <vector>
#include <atomic>
#include <memory>
#include <filesystem>

class TaskQueue;

class Task
{    
    enum class State
    {
        READY,
        READY_CHILD,
        ACTIVE,
        WAIT_CHILD,
        DONE
    };

public:
    Task(const std::filesystem::path& path, TaskQueue& queue);

    int id() const;
    int result() const;

    bool isDone() const;

    void process();
    void readyChild();

    void print( int deep = 0 );

private:
    void finalize();

private:
    const int m_id;
    std::atomic< State > m_state;
    size_t m_result;
    std::filesystem::path m_path;
    TaskQueue& m_queue;

    std::vector< std::shared_ptr< Task > > m_children;
};

#endif
