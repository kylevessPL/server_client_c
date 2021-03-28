#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

void* client_handler(void* args);

void handle_sqrt_query(int req_id, int sockfd);
void handle_datetime_query(int req_id, int sockfd);

char* get_current_datetime();

#endif //CLIENT_HANDLER_H
