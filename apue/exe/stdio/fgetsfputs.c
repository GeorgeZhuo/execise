#include "apue.h"

int
main(void)
{

    char	buf[MAXLINE];
    /* using fgets and stdin read input from stdin 
     * output to the stdout
     */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
	if (fputs(buf, stdout) == EOF) {
	    err_sys("output error");
	}
    }

    if (ferror(stdin))
	err_sys("input error");

    exit(0);
}
