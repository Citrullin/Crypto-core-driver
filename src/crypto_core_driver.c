#include <string.h>

#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uart.h>
#endif

#include <ulfius.h>
#include <uart.h>

#include "config.h"
#include "callbacks.h"

//Todo: Use fd as parameter for callback function. In order to have multiple fds.
int uart_fd;

char * read_file(const char * filename) {
    char * buffer = NULL;
    long length;
    FILE * f = fopen (filename, "rb");
    if (f != NULL) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = o_malloc (length + 1);
        if (buffer != NULL) {
            fread (buffer, 1, length, f);
            buffer[length] = '\0';
        }
        fclose (f);
    }
    return buffer;
}

void add_endpoint_declarations(struct _u_instance * instance_ptr){
    ulfius_add_endpoint_by_val(instance_ptr, "POST", "", NULL, 0, &callback_api, NULL);

    ulfius_set_default_endpoint(instance_ptr, &callback_not_found, NULL);
}

void add_response_header(struct _u_instance * instance_ptr){
    u_map_put(instance_ptr->default_headers, "Access-Control-Allow-Origin", "*");
}

void start_server(struct _u_instance * instance_ptr, int argc, char **argv){
    int ret;

    if (argc == 4 && o_strcmp("-secure", argv[1]) == 0) {
        // If command-line options are -secure <key_file> <cert_file>, then open an https connection
        char * key_pem = read_file(argv[2]), * cert_pem = read_file(argv[3]);
        ret = ulfius_start_secure_framework(instance_ptr, key_pem, cert_pem);
        o_free(key_pem);
        o_free(cert_pem);
    } else {
        // Open an http connection
        ret = ulfius_start_framework(instance_ptr);
    }

    if (ret == U_OK) {
        y_log_message(Y_LOG_LEVEL_DEBUG, "Start %sframework on port %d", ((argc == 4 && o_strcmp("-secure", argv[1]) == 0)?"secure ":""), instance_ptr->port);

        // Wait for the user to press <enter> on the console to quit the application
        getchar();
    } else {
        y_log_message(Y_LOG_LEVEL_DEBUG, "Error starting framework");
    }
}

int main (int argc, char **argv) {
    uart_fd = uart_init();

    struct _u_instance instance;

    y_init_logs("crypto_core_driver", Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Starting crypto_core_driver");

    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        y_log_message(Y_LOG_LEVEL_ERROR, "Error ulfius_init_instance, abort");
        return(1);
    }

    instance.max_post_body_size = 2048;

    add_response_header(&instance);
    add_endpoint_declarations(&instance);

    start_server(&instance, argc, argv);
    y_log_message(Y_LOG_LEVEL_DEBUG, "End framework");

    y_close_logs();

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return 0;
}

