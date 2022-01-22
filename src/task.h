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
    Task(std::filesystem::path  path, TaskQueue& queue, Task* parent = nullptr );

    [[nodiscard]] unsigned long result() const;
    [[nodiscard]] bool isDone() const;

    bool process();
    void readyChildren();

private:
    bool finish();
    std::string formatedSize() const;

private:
    std::atomic< State > m_state;
    unsigned long m_result;
    std::filesystem::path m_path;
    TaskQueue& m_queue;

    Task* m_parent;
    std::vector< std::shared_ptr< Task > > m_children;
};

#endif
