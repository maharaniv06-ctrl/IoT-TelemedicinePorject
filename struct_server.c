/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
	char nama[32];
	char alamat[64];
	char nomor_ktp[20];
} humanid_t;

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
	humanid_t *aMan;
/*  Remove any old socket and create an unnamed socket for the server.  */


	aMan = (humanid_t*)malloc(sizeof(humanid_t));
	
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9735);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;

        printf("server waiting\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);
printf("server accepted\n");
/*  We can now read/write to client on client_sockfd.  */

        read(client_sockfd, aMan, sizeof(humanid_t));
printf("server read\n");
		printf("%s\n",aMan->nama);
		printf("%s\n",aMan->alamat);
		printf("%s\n",aMan->nomor_ktp);
 //       ch++;
 //       write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}

