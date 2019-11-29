#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int status;
	char buffer[256];
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_port = htons(1234);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0 ){
		perror("ERROR opening socket");
		exit(1);
	}
	
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
		perror("ERROR connecting");
		exit(1);
	}
	
	while(1) {
		write(sockfd,buffer,strlen(buffer));
		bzero(buffer,256);
		read(sockfd,buffer,255);
		printf("%s",buffer);
		scanf("%s",buffer);
		write(sockfd,buffer,strlen(buffer));
	
		switch(buffer[0]){
		  case '1' : /*DNS*/
			n = 0;
			bzero(buffer,256);
			status = read(sockfd,buffer,255);
			printf("%s",buffer);
			bzero(buffer,256);
			scanf("%s",buffer);
			status = write(sockfd,buffer,strlen(buffer));
			bzero(buffer,256);
			status = read(sockfd,buffer,255);
			printf("address get from domain name: %s\n\n",buffer);
		  break;
		  case '2' : /*query*/
			n = 0;
			bzero(buffer,256);
			status = read(sockfd, buffer, 255);
			printf("%s", buffer);
			bzero(buffer,256);
			scanf("%s",buffer);
			status = write(sockfd,buffer,strlen(buffer));
			bzero(buffer,256);
			status = read(sockfd, buffer, 255);
			printf("Email get from server: %s\n\n",buffer);
			break;
		  case '3':
			n = 1;
			break;
		  default:
			n = 4;
			printf("Don't provide the kind of service.\n\n");
		}
		if (n == 1){
			close(sockfd);
			break;
		}
	}
	return 0 ;
}





	

	
