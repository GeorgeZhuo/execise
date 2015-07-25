#include "apue.h"

int main(int argc, char *argv[])
{
    if (chdir("/tmp") < 0)
	err_sys("chidir faliled");

    printf("chdir to /tmp successed\n");
    
    exit(0);
    return 0;
}
