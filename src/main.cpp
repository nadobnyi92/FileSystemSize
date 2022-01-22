#include "fs_cli.h"

int main()
{
    FileSystemCli cli;
    cli.initThreadPool( 1 );
    cli.start();

    return 0;
}

