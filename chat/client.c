#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

const char stdport[] = "33185";

int square (int num, int ex) {
	int res = 1;

	for (int i = 0; i < ex; i++)
		res *= num;
	return res;
}

int main (int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[2000] , server_reply[2000], server_ip_port[23], c;
	char server_ip[17], server_port[6];
	int server_p = 0;

	//Read an IP:port of server
	int i;
	if (argc == 1) {
		puts("Введите IP сервера: ");
		for (i = 0; i < 22; i++) {
			c = fgetc(stdin);
			if (c == '\n')
				break;
			server_ip_port[i] = c;
		}
		server_ip_port[i] = '\0';
	} else 
		for (int o = 0; o <= strlen(argv[1]); o++) server_ip_port[o] = argv[1][o];
	for (i = 0; server_ip_port[i] != ':' && server_ip_port[i] != '\0'; i++)
		server_ip[i] = server_ip_port[i];
	server_ip[i] = '\0';
	if (server_ip_port[i] == ':') {
		i++;
		for (int o = 0; server_ip_port[i] != '\0'; o++) {
			server_port[o] = server_ip_port[i];
			i++;
		}
	} else
		for (int o = 0; o < sizeof server_port; o++) server_port[o] = stdport[o];
	unsigned char ex = 0;
	for (int o = strlen(server_port) - 1; o != -1; o--) {
		server_p += square(10, ex) * (server_port[o] - 48);
		ex++;
	}

    //Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(server_p);

	//Connect to remote server
	printf("IP: %s, port: %i, trying...\n", server_ip, server_p);
	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}
	puts("Connected");
	puts("Привет!");

	//keep communicating with server
	while (1)
	{
		printf("Вы:\n");
		for (int o = 0; o < sizeof(message); o++)
			if ((message[o] = getchar()) == EOF)
				break;

		//Send some data
		if(send(sock, message, strlen(message), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}

		message[0] = EOF;

		//Receive a reply from the server
		if(recv(sock, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}

		printf("Никита Кот:\n");
		for (int o = 0; o < sizeof(server_reply); o++)
			if (server_reply[o] == EOF)
				break;
			else
				putchar(server_reply[o]);
		server_reply[0] = EOF; 
	}

	close(sock);
	return 0;
}
