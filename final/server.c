#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct student{
	char ID[256];
	char email[256];
}data;

int main(int argc, char *argv[]){
	int a=0;
	int n=0;
	FILE *fPtr;
	data table[100];
	fPtr = fopen("query.txt","r");
	while(fscanf(fPtr,"%s%s",table[a].ID,table[a].email)!=EOF){
		a++;
	}

	int sockfd, newsockfd, client;
	char buffer[256];
	char ip[256]; 
	struct sockaddr_in serv_addr, cli_addr;
	int status;
	int addr_size;
	int match,intbuffer;
	struct hostent *host;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		perror("ERROR opening socket");
		exit(1);
	}

	bzero((char *)&serv_addr, sizeof(serv_addr)); 
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(1234);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0){
		perror("ERROR on binding)");
		exit(1);
	}

	/*Now start listening for the cients*/
	while(1) {
		listen(sockfd,10);
		addr_size = sizeof(cli_addr);
		printf("waiting for connection~\n");

		/*Accept*/
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &addr_size);
		if (newsockfd < 0) {
			perror("ERROR on accept");
			exit(1);
		}
		while(1) {
			/*start communicating*/
			read(newsockfd,buffer,255);
			bzero(buffer,256);
			strcpy(buffer, "What's your requirement? 1.DNS 2.QUERY 3.QUIT: ");
			write(newsockfd, buffer,strlen(buffer));
			bzero(buffer,256);
			bzero(ip,256);
			status = read( newsockfd, buffer, 255);
	
			if (status < 0) {
				perror("ERROR reading from socket");
				exit(1);
			}
			/*intbuffer = atoi(buffer);*/
			switch(buffer[0]){
			  case '1' : /*DNS*/
				n = 0;
				strcpy(buffer,"Input URL address : ");
				write(newsockfd,buffer,strlen(buffer));
				bzero(buffer, 256);
				status = read(newsockfd, buffer,255);
				/*printf("read:%s\n",buffer);*/
				host = gethostbyname(buffer);
			  if(host == NULL) {
				strcpy(ip, "No such domain name");
			  }
			  else {
				strcpy(ip, inet_ntoa(*((struct in_addr*)host->h_addr)));
			  }
			  status = write(newsockfd,ip,strlen(ip));
			  /*printf("write:%s\n",ip);*/
			  if(status < 0) {
				perror("ERROR writing to socket\n");
				exit(1);
			  }
			  break;
			  case '2' : /*query*/
				match = 0;
				n = 0;
				strcpy(buffer, "Input student ID : ");
				write(newsockfd, buffer, strlen(buffer));
				bzero(buffer,256);
				bzero(ip,256);
				status = read(newsockfd,buffer,255);
				for(int i = 0 ; i < a ; i++){
				  if(strcmp(buffer, table[i].ID) == 0){
					strcpy(ip, table[i].email);
				  	match = 1;
				  }
				}
				if (match == 0 ){
					strcpy(ip, "No such student ID");
				}
				status = write(newsockfd, ip,255);
				if (status < 0){
					perror("ERROR writing to socket\n");
					exit(1);
				}
			  	break;
			  case '3' :
				n = 1;
				break;
			  default:
				n = 4;
			}
			if (n == 1){
				break;
			}
		}
	}
	return 0;
}
