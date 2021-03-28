#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <client_handler.h>

int main()
{
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    bind(server_sockfd, (struct sockaddr*) &server_address, sizeof(struct sockaddr_in));
    listen(server_sockfd, 5);
    printf("Waiting for client request...\n");
    while (1)
    {
        pthread_t thread;
        socklen_t client_len = sizeof(client_address);
        int client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_address, &client_len);
        pthread_create(&thread, NULL, &client_handler, (void*) &client_sockfd);
        pthread_detach(thread);
    }
}