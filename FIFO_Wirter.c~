#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFOSIZE 128
#define FIFO "fifo"
#define MSGSIZE 50

int main(){
	pid_t pid;
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	char rcvBuffer[BUFSIZ];

	int fd, i;
	char fifoBuf[FIFOSIZE];

	char *cnntmsg;
	char *rcvmsg;

	cnntmsg = "Connect Success!\n";

	s_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(3001);

	if(mkfifo(FIFO, 0666)==-1){
		if(errno != 17){
			exit(1);
		}
	}
	if((fd=open(FIFO, O_WRONLY))==-1){
		perror("fifo file open failed");
		exit(1);
	}



	if(bind(s_socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1){
		printf("Can not Bind\n");
		return -1;
	}

	if(listen(s_socket, 5) == -1){
		printf("listen Fail\n");
		return -1;
	}

	len = sizeof(c_addr);
	c_socket = accept(s_socket, (struct sockaddr*)&c_addr, &len);    

	memset(rcvBuffer, 0, BUFSIZ); 
	send(c_socket, cnntmsg, strlen(cnntmsg), 0);

	if(mkfifo(FIFO, 0666)==-1){
		if(errno != 17){
			exit(1);
		}
	}
	if((fd=open(FIFO, O_WRONLY))==-1){
		perror("fifo file open failed");
		exit(1);
	}



	while(1){
		while((n=read(c_socket, rcvBuffer, sizeof(rcvBuffer))) != 0){
			if(n<0)
			{
				printf("receive error\n");
				return -1;
			}

			rcvBuffer[n] = '\0';
			printf("%s", rcvBuffer);

			strcpy(fifoBuf, rcvBuffer);
			if(write(fd, fifoBuf, FIFOSIZE)==-1){
				perror("fifo file srtie failed");
				exit(1);
			}
			//close(fd);
		}
		close(fd);
		close(c_socket);
	}
	close(s_socket);
	return 0;
}
