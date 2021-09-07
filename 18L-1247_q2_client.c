/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Get Input from the User
        
        printf("Enter Message: ");
        gets(client_message);                                     //One is that gets() will only get character string data. 
                                                       //		will get only one variable at a time.
																//  reads characters from stdin and loads them into str
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        int x = strlen(server_message);
        	int count = 0, vow = 0, l = 0, s = 0, i = 0, e = 0;
   		for (i = 0; i < x; i++)
		{
			s = i;							// starting index
			for (;server_message[i] != ' ' && i < x - 1; i++)
			{
				if (server_message[i] == 'a' || server_message[i] == 'A' || server_message[i] == 'e' || server_message[i] == 'E' || server_message[i] == 'i' || server_message[i] == 'I' || server_message[i] == 'o' || server_message[i] == 'O' || server_message[i] == 'u' || server_message[i] == 'U')
					vow++;
				count++;
			}
			e = i - 1; 							// ending index
			if (vow  == 0)
			{
				for (l = 0; l < count/2; l++, s++, e--)
				{
					char temp = server_message[s];
					server_message[s] = server_message[e];
					server_message[e] = temp;
				}
			}
			
			vow = 0;
			count = 0;
		}
       
        
        printf("Inverted Server Message: %s\n",server_message);
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}
