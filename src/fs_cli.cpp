#include "fs_cli.h"

#include <iostream>
#include <string>

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
            std::cout << "calc size: " << result << std::endl;
        }
    }
}
   
