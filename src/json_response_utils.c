#include <string.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <ulfius.h>

void json_response_set_error_message(json_t *json, char *message) {
    json_t *response_message_json = json_string(message);
    json_object_set_new(json, "message", response_message_json);
}