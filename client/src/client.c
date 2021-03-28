#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <protocol.h>

#define NUMBER 17.26

void send_datetime_request(int sockfd);
void send_sqrt_request(int sockfd);

int main()
{
    struct sockaddr_in address;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    int result = connect(sockfd, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
    {
        perror("oops: netclient");
        return EXIT_FAILURE;
    }
    send_datetime_request(sockfd);
    send_sqrt_request(sockfd);
    while (1)
    {
        get_header_type(sockfd);
        int req_id = get_req_id(sockfd);
        if (req_id == 1)
        {
            int length = get_datetime_length(sockfd);
            char* buf = malloc(sizeof(char) * length);
            read(sockfd, buf, length);
            printf("Current server datatime: %s\n", buf);
            free(buf);
        }
        else
        {
            char* buf = malloc(sizeof(double));
            read(sockfd, buf, sizeof(double));
            double num = get_sqrt_number(buf);
            printf("Sqrt of number: %lf\n", num);
            free(buf);
        }
    }
}

void send_sqrt_request(int sockfd)
{
    sqrt_message sqrt_query_message;
    sqrt_query_message.header[0] = 0;
    sqrt_query_message.header[1] = 0;
    sqrt_query_message.header[2] = 0;
    sqrt_query_message.header[3] = 1;
    sqrt_query_message.req_id = 2;
    sqrt_query_message.num = NUMBER;
    size_t sqrt_frame_size = sizeof(int) * 4 + sizeof(int) + sizeof(double);
    char* sqrt_frame = encapsulate_sqrt_message(sqrt_query_message);
    write(sockfd, sqrt_frame, sqrt_frame_size);
}

void send_datetime_request(int sockfd)
{
    datetime_query datetime_query;
    datetime_query.header[0] = 0;
    datetime_query.header[1] = 0;
    datetime_query.header[2] = 0;
    datetime_query.header[3] = 2;
    datetime_query.req_id = 1;
    size_t datetime_frame_size = sizeof(int) * 4 + sizeof(int);
    char* datetime_frame = encapsulate_datetime_query(datetime_query);
    write(sockfd, datetime_frame, datetime_frame_size);
}
