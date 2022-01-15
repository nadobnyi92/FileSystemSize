#include "fs_cli.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
void exec_task( TaskQueue& tasks )
{
    while(1)
    {
        auto task = tasks.getTask();
        if(task)
        {
            task->process();
            if( !task->isDone() )
            {
                tasks.addTask( task );
            }
        }
        else
        {
            std::this_thread::sleep_for( 200ms );
        }
    }
}

void FileSystemCli::start()
{
    while( true )
    {
        std::string result;

        std::cout << "#fs > ";
        std::cin >> result;

        if( result == "exit" )
        {
            break;
        }
        else
        {
            std::filesystem::path path{ result };
            if(std::filesystem::exists( path ) )
            {
                m_tasks.createTask( path );
            }
        }
    }
}

void FileSystemCli::initThreadPool( int size )
{
    for( int i = 0; i < size; ++i )
    {
        m_threads.emplace_back( std::thread( exec_task, std::ref( m_tasks ) ) );
    }
}
   
