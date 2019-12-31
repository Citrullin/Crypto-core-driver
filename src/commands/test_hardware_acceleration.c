#include <ulfius.h>
#include <uart.h>

void test_hardware_acceleration_handle_request(json_t *json_ptr, struct _u_response *response) {
    uart_write(json_ptr);
    char * result = uart_read();
    ulfius_set_string_body_response(response, 200, result);
}