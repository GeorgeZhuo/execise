#include "apue.h"
#include <errno.h>

void make_temp(char *temp);

int main(int argc, char *argv[])
{
    
    /* right way */
    char good_template[] = "/tmp/dirXXXXXX";
    /* wrong way*/
    char *bad_template = "/tmp/dirXXXXXXX";
    
    printf("trying to create first temp file...\n");
    make_temp(good_template);
    
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    
    exit(0);
}

void
make_temp(char *temp) {


    int fd;
    struct stat statbuf;
    
    if ((fd = mkstemp(temp)) < 0) {
	err_sys(" can't create temp file");
    }
    printf("tempj name = %s\n", temp);
    close(fd);

    if (stat(temp, &statbuf) < 0) {
	
	if (errno = ENOENT) {
	    printf("file doesn't exist\n'");
	} else {
	    err_sys("stat failed");
	}
    } else {
	printf("file exit\n");
	unlink(temp);
    }

}
