#ifndef FILE_SYSTEM_CLI_H
#define FILE_SYSTEM_CLI_H

#include "task_queue.h"

#include <vector>
#include <thread>

class FileSystemCli
{
public:
    void start();

    void initThreadPool( int size );

private:
    std::vector< std::thread > m_threads;
    TaskQueue m_tasks; 
};

#endif //FILE_SYSTEM_CLI_H
