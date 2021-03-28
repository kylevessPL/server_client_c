#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <netinet/in.h>
#include <protocol.h>
#include <endianness.h>
#include <string.h>

enum header_type validate_header_type(const int* header)
{
    if (header[0] != 0 || header[1] != 0 || header[2] != 0)
    {
        return MALFORMED_HEADER;
    }
    if (header [3] == 1)
    {
        return SQRT_HEADER;
    }
    else if (header [3] == 2)
    {
        return DATETIME_HEADER;
    }
    return MALFORMED_HEADER;
}

char* encapsulate_sqrt_message(sqrt_message message)
{
    uint32_t req_id = htonl(message.req_id);
    uint64_t num = htond(message.num);
    uint32_t header[4];
    for (int i = 0; i < 4; ++i)
    {
        header[i] = htonl(message.header[i]);
    }
    char* frame = malloc(sizeof(char) * 200);
    char* frame_tmp = frame;
    memcpy(frame_tmp, header, sizeof(int) * 4);
    frame_tmp += sizeof(int) * 4;
    memcpy(frame_tmp, &req_id, sizeof(int));
    frame_tmp += sizeof(int);
    memcpy(frame_tmp, &num, sizeof(double));
    return frame;
}

char* encapsulate_datetime_query(datetime_query query)
{
    int req_id = htonl(query.req_id);
    int header[4];
    for (int i = 0; i < 4; ++i)
    {
        header[i] = htonl(query.header[i]);
    }
    char* frame = malloc(sizeof(char) * 200);
    char* frame_tmp = frame;
    memcpy(frame_tmp, header, sizeof(int) * 4);
    frame_tmp += sizeof(int) * 4;
    memcpy(frame_tmp, &req_id, sizeof(int));
    return frame;
}

char* encapsulate_datetime_response(datetime_response response)
{
    size_t len = htonl(response.len);
    int req_id = htonl(response.req_id);
    int header[4];
    for (int i = 0; i < 4; ++i)
    {
        header[i] = htonl(response.header[i]);
    }
    char* frame = malloc(sizeof(char) * 200);
    char* frame_tmp = frame;
    memcpy(frame_tmp, header, sizeof(int) * 4);
    frame_tmp += sizeof(int) * 4;
    memcpy(frame_tmp, &req_id, sizeof(int));
    frame_tmp += sizeof(int);
    memcpy(frame_tmp, &len, sizeof(size_t));
    frame_tmp += sizeof(size_t);
    memcpy(frame_tmp, response.datetime, response.len);
    return frame;
}

enum header_type get_header_type(int sockfd)
{
    char* buf = malloc(sizeof(int) * 4);
    read(sockfd, buf, sizeof(int) * 4);
    char* frame = buf;
    int header_tmp[4];
    memcpy(&header_tmp, frame, sizeof(int) * 4);
    int header[4];
    for (int i = 0; i < 4; ++i)
    {
        header[i] = ntohl(header_tmp[i]);
    }
    free(buf);
    return validate_header_type(header);
}

int get_req_id(int sockfd)
{
    char* buf = malloc(sizeof(int));
    read(sockfd, buf, sizeof(int));
    char* frame = buf;
    int req_id;
    memcpy(&req_id, frame, sizeof(int));
    free(buf);
    return ntohl(req_id);
}

double get_sqrt_number(char* frame)
{
    char* frame_tmp = frame;
    uint64_t number;
    memcpy(&number, frame_tmp, sizeof(double));
    return ntohd(number);
}

size_t get_datetime_length(int sockfd)
{
    char* buf = malloc(sizeof(size_t));
    read(sockfd, buf, sizeof(size_t));
    char* frame = buf;
    size_t len;
    memcpy(&len, frame, sizeof(size_t));
    free(buf);
    return ntohl(len);
}
