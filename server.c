#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 128
#define FIFO "fifo"

void main(int argc, char *argv[]){
	int fd;
	int counter=0;
	char buffer[SIZE];

	if((fd=open(FIFO, O_RDWR))==-1){
		perror("mkfifo failed");
		exit(1);
	}

	while(1){
		/*if(read(fd, buffer, SIZE)==-1){
			perror("read failed");
			exit(1);
		}*/

		memset(buffer, 0, SIZE);
		read(fd, buffer, SIZE);
		if(!strcmp(buffer, "quit"))
			exit(0);

		printf("(count:%d) receive message : %s\n", counter++, buffer);
	}
	close(fd);
}
