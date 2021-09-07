/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
        char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

        //Cleaning the Buffers
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//
        
        //Creating Socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
       
        
        
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2000);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        while(1){
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
		
		
		
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);          // heree particular client k liye new socket create kr rhaa ha
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		       //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation
        
        //Receive the message from the client
        
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }

        
        //Send the server message back to client
       	int x = strlen(client_message);
       	/*char id = client_message[len - 1];
        char arr100[100] = "Hello I am server. Your received id is ";
             
      	strncat(arr100, &id, 1);
        strcpy(server_message, arr100);
   */
   		int count = 0, vow = 0, l = 0, s = 0, i = 0, e = 0;
   		for (i = 0; i < x; i++)
		{
			s = i;							// starting index
			for (; client_message[i] != ' ' && i < x - 1; i++)
			{
				if (client_message[i] == 'a' || client_message[i] == 'A' || client_message[i] == 'e' || client_message[i] == 'E' || client_message[i] == 'i' || client_message[i] == 'I' || client_message[i] == 'o' || client_message[i] == 'O' || client_message[i] == 'u' || client_message[i] == 'U')
					vow++;
				count++;
			}
			e = i - 1; 							// ending index
			if (vow >= 1)
			{
				for (l = 0; l < count/2; l++, s++, e--)
				{
					char temp = client_message[s];
					client_message[s] = client_message[e];
					client_message[e] = temp;
				}
			}
			
			vow = 0;
			count = 0;
		}
       
       strcpy(server_message, client_message);
       printf("Inverted Client Message: %s\n",client_message);
        //server_message[len] = id;
        //server_message[len + 1] = '\0';
        
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        }  
        //Closing the Socket
        
        close(client_sock);
        close(socket_desc);
        return 0;       
}
