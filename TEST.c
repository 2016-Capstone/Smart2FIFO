#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/tcp.h>

#define PORT 443
#define DEST_IP "210.125.31.34"

int main() {
	int c_socket;
	struct sockaddr_in c_addr;
	int len;
	char rcv_buf[BUFSIZ];
	int n;
	int option = 1;
	char* hello_msg = "ID=1\n";
	int is_first = 1;
	pid_t pid;
	int status;

	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	if ( setsockopt(c_socket, IPPROTO_TCP, TCP_NODELAY, &option, sizeof(option)) == -1){
		printf("setsockopt err");
		return -1;
	}

	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(DEST_IP);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	if ( connect(c_socket, (struct sockaddr*)&c_addr, sizeof(c_addr)) == -1 ) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}

	if( (pid=fork()) == 0 ) {
		sleep(1);
		write(c_socket, hello_msg, sizeof(hello_msg));
		close(c_socket);
		return 24;
	} else {
		while(!waitpid(-1, &status, WNOHANG)) {
			sleep(0.1);
		}

		if(WIFEXITED(status))
			printf("Child send %d \n", WEXITSTATUS(status));

		while(1) {

			if ( n = read(c_socket, rcv_buf, sizeof(rcv_buf)) < 0) {
				close(c_socket);
				return -1;
			}

			//rcv_buf[n] = '\0';
			printf("%s", rcv_buf);

			memset(rcv_buf, '\0', BUFSIZ);
		}

	}

//	write(c_socket, hello_msg, sizeof(hello_msg)+1);
/*	if ( write(c_socket, hello_msg, sizeof(hello_msg)) != sizeof(hello_msg)){
		printf("send failed");
		return -1;
	}
*/
/*
	if (fork() == 0){
		sleep(3);
		write(c_socket, hello_msg, sizeof(hello_msg));
		close(c_socket);
		return -1;
	}
*/
/*	while (1) {
		if(is_first){
			write(c_socket, hello_msg, sizeof(hello_msg));
			is_first = 0;
		}

		if ( n = read(c_socket, rcv_buf, sizeof(rcv_buf)) < 0) {
			close(c_socket);
			return -1;
		}

		//rcv_buf[n] = '\0';
		printf("%s", rcv_buf);
		
		memset(rcv_buf, '\0', BUFSIZ);
	}
*/

}
