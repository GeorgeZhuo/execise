#include "apue.h"

int main(int argc, char *argv[])
{
    char name[L_tmpnam], line[MAXLINE];
    FILE  *fp;

    /* first temp name */
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);

    /* second temp name*/
    printf("%s\n", name);
    if ((fp = tmpfile()) == NULL) 
	err_sys("tmpfile error");
    
    fputs("one line of output\n", fp);
    rewind(fp);

    if (fgets(line, sizeof(line), fp) == NULL) {
	err_sys("fgets error");
    }
   
    fputs(line, stdout);
    
    exit(0);
}
