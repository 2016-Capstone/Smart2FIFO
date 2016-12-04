#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 128
#define FIFO "fifo"

void main(int argc, char *argv[]){
	int fd, i, counter = 0;
	int file;
	char buffer[SIZE];

	if((fd=open(FIFO, O_WRONLY))==-1){
		perror("open failed");
		exit(1);
	}

	for(i=1; i<argc; ++i){
		strcpy(buffer, argv[i]);
		if(write(fd, buffer, SIZE)==-1){
			perror("write failed");
			exit(1);
		}
	}
	close(fd);
	exit(0);
}



















