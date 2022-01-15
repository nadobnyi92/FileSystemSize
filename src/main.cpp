#include "fs_cli.h"

int main()
{
    FileSystemCli cli;
    cli.initThreadPool( 4 );
    cli.start();

    return 0;
}

