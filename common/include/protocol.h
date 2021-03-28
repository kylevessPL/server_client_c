#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stddef.h>

enum header_type
{
    MALFORMED_HEADER,
    SQRT_HEADER,
    DATETIME_HEADER,
};

typedef struct datetime_query
{
    int header[4];
    int req_id;
} datetime_query;

typedef struct datetime_response
{
    int header[4];
    int req_id;
    size_t len;
    char* datetime;
} datetime_response;

typedef struct sqrt_message
{
    int header[4];
    int req_id;
    double num;
} sqrt_message;

enum header_type get_header_type(int sockfd);
enum header_type validate_header_type(const int* header);

int get_req_id(int sockfd);
double get_sqrt_number(char* frame);
size_t get_datetime_length(int sockfd);

char* encapsulate_sqrt_message(sqrt_message message);
char* encapsulate_datetime_query(datetime_query query);
char* encapsulate_datetime_response(datetime_response response);

#endif //PROTOCOL_H
