#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <protocol.h>
#include <client_handler.h>

void* client_handler(void* args)
{
    int sockfd = *((int*) args);
    while (1)
    {
        enum header_type header_type = get_header_type(sockfd);
        int req_id = get_req_id(sockfd);
        switch (header_type)
        {
            case SQRT_HEADER:
                printf("SQRT QUERY RECEIVED\n");
                handle_sqrt_query(req_id, sockfd);
                break;
            case DATETIME_HEADER:
                printf("DATETIME QUERY RECEIVED\n");
                handle_datetime_query(req_id, sockfd);
                break;
            default:
                printf("MALFORMED QUERY HEADER RECEIVED\n");
                break;
        }
    }
}

void handle_sqrt_query(int req_id, int sockfd)
{
    char* buf = malloc(sizeof(double));
    read(sockfd, buf, sizeof(double));
    double num = get_sqrt_number(buf);
    printf("Query number: %lf\n", num);
    sqrt_message message;
    message.header[0] = 1;
    message.header[1] = 0;
    message.header[2] = 0;
    message.header[3] = 1;
    message.req_id = req_id;
    message.num = sqrt(num);
    printf("Query number sqrt: %lf\n", message.num);
    size_t frame_size = sizeof(int) * 4 + sizeof(int) + sizeof(double);
    char* frame = encapsulate_sqrt_message(message);
    write(sockfd, frame, frame_size);
    printf("SQRT RESPONSE SENT\n");
    free(buf);
    free(frame);
}

void handle_datetime_query(int req_id, int sockfd)
{
    char* datetime = get_current_datetime();
    printf("Current server datetime: %s\n", datetime);
    datetime_response response;
    response.header[0] = 1;
    response.header[1] = 0;
    response.header[2] = 0;
    response.header[3] = 2;
    response.req_id = req_id;
    response.datetime = datetime;
    response.len = strlen(datetime) + 1;
    size_t frame_size = sizeof(int) * 4 + sizeof(int) + sizeof(size_t) + response.len;
    char* frame = encapsulate_datetime_response(response);
    write(sockfd, frame, frame_size);
    printf("DATETIME RESPONSE SENT\n");
    free(datetime);
    free(frame);
}

char* get_current_datetime()
{
    time_t rawtime;
    time(&rawtime);
    char* datetime = malloc(sizeof(char) * 30);
    int size = sprintf(datetime, "%s", asctime(localtime(&rawtime)));
    datetime[size - 1] = '\0';
    return datetime;
}
