#include <string.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <ulfius.h>

#ifndef ULFIUS_JSON_RESPONSE_UTILS_H
#define ULFIUS_JSON_RESPONSE_UTILS_H

void json_response_set_error_message(json_t *json, char *message);

#endif //ULFIUS_JSON_RESPONSE_UTILS_H
