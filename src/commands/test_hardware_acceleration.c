#include <ulfius.h>

void test_hardware_acceleration_handle_request(json_t *json_ptr, struct _u_response *response) {
    ulfius_set_string_body_response(response, 200, "testHardwareAcceleration");
}