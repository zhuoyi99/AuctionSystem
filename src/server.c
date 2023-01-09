
#include "server.h"
#include "helpers.h"
#include "protocol.h"
#include <pthread.h>
#include <signal.h>
#include <assert.h>

const char exit_str[] = "exit";

pthread_mutex_t buffer_lock;

int total_num_msg = 0;
int listen_fd;

void sigint_handler(int sig)
{
    printf("shutting down server\n");
    close(listen_fd);
    exit(0);
}

int server_init(int server_port){
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully created\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server_port);

    int opt = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(opt))<0)
    {
	perror("setsockopt");exit(EXIT_FAILURE);
    }

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully binded\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 1)) != 0) {
        printf("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Server listening on port: %d.. Waiting for connection\n", server_port);

    return sockfd;
}


/*
log in -> store user information
insert the job into a shared buffer
*/

void* process_client(void* clientfd_ptr){
    char* username;
    petr_header* msg_header = malloc(sizeof(petr_header));
    int client_fd = *(int *)clientfd_ptr;
    free(clientfd_ptr);

    if(rd_msgheader(client_fd,msg_header) == -1){
        printf("something's off with reading a message");
        
    }
    char buffer[BUFFER_SIZE];
    switch (msg_header->msg_type)
    {
    
    case LOGOUT:
        close(client_fd);

    default:
        //put the job into buffer
        break;
    }
    
    return NULL;

}

//check if user name exist
//if user exists, check the password
//if not, create a new user, insert into user list
//return 0 if sucess, -1 for error
int  process_login(int client_fd){
    
    petr_header msg_header;
    assert(rd_msgheader(client_fd, &msg_header) == 0);
    assert(msg_header.msg_type == LOGIN);

    //read msg body
    char buffer[BUFFER_SIZE];
    int read_count = read(client_fd, buffer, msg_header.msg_len);
    assert(read_count == msg_header.msg_len);

    //split to name&pwd
    char* username = strtok(buffer, "\r\n");
    char* pwd = strtok(NULL, "\r\n");
    assert(username != NULL && pwd != NULL);


    return 0;
}



/*
void *process_client(void* clientfd_ptr){
    int client_fd = *(int *)clientfd_ptr;
    free(clientfd_ptr);
    int received_size;
    fd_set read_fds;

    int retval;
    while(1){
        FD_ZERO(&read_fds);
        FD_SET(client_fd, &read_fds);
        retval = select(client_fd + 1, &read_fds, NULL, NULL, NULL);
        if (retval!=1 && !FD_ISSET(client_fd, &read_fds)){
            printf("Error with select() function\n");
            break;
        }

        pthread_mutex_lock(&buffer_lock); 

        bzero(buffer, BUFFER_SIZE);
        received_size = read(client_fd, buffer, sizeof(buffer));
        if(received_size < 0){
            printf("Receiving failed\n");
            break;
        }else if(received_size == 0){
            continue;
        }
            
        if(strncmp(exit_str, buffer, sizeof(exit_str))==0){
            printf("Client exit\n");
            break;
        }
        total_num_msg ++;
        // print buffer which contains the client contents
        printf("Receive message from client: %s\n", buffer);
        printf("Total number of received messages: %d\n", total_num_msg);

        sleep(1); //mimic a time comsuming process 

        // and send that buffer to client
        int ret = write(client_fd, buffer, received_size);
        pthread_mutex_unlock(&buffer_lock);

        if (ret < 0){
            printf("Sending failed\n");
            break;
        }
        printf("Send the message back to client: %s\n", buffer);
    }
    // Close the socket at the end
    printf("Close current client connection\n");
    close(client_fd);
    return NULL;
}*/

void run_server(int server_port){
    listen_fd = server_init(server_port); // Initiate server and start listening on specified port
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    pthread_t tid;

    while(1){
        // Wait and Accept the connection from client
        printf("Wait for new client connection\n");
        int* client_fd = malloc(sizeof(int));
        *client_fd = accept(listen_fd, (SA*)&client_addr, &client_addr_len);
        if (*client_fd < 0) {
            printf("server acccept failed\n");
            exit(EXIT_FAILURE);
        }

        if(process_login(*client_fd) < 0){

        }
        exit(-1);


        printf("Client connetion accepted\n");
        pthread_create(&tid, NULL, process_client, (void *)client_fd); 
    }
    //bzero(buffer, BUFFER_SIZE);
    close(listen_fd);
    return;
}

int main(int argc, char* argv[])
{

    int opt;

    unsigned int port = 0;
    // while ((opt = getopt(argc, argv, "p:")) != -1) {
    //     switch (opt) {
    //     case 'p':
    //         port = atoi(optarg);
    //         break;
    //     default: /* '?' */
    //         fprintf(stderr, "Server Application Usage: %s -p <port_number>\n",
    //                 argv[0]);
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // if (port == 0){
    //     fprintf(stderr, "ERROR: Port number for server to listen is not given\n");
    //     fprintf(stderr, "Server Application Usage: %s -p <port_number>\n",
    //                 argv[0]);
    //     exit(EXIT_FAILURE);
    // }
 
  
    port = atoi(argv[1]);

    FILE* input = fopen(argv[2],"r"); 
  
    parseAuctions(input);
  
    run_server(port);

    return 0;
}
