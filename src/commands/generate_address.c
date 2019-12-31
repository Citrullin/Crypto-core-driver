#include <stdbool.h>
#include <ulfius.h>
#include "error_util.h"
#include <uart.h>

struct generate_address_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *tryte_array_ptr;
};

struct generate_address_validation_result generate_address_validation_result(json_t *json_ptr) {
    struct generate_address_validation_result result = {.successful = false};

    json_t *key_json_ptr = json_object_get(json_ptr, "key");
    if (json_is_null(key_json_ptr) || key_json_ptr == NULL) {
        result.validation_error = ERROR_KEY_MISSING;

        return result;
    }

    if (key_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_KEY_NOT_NUMBER;

        return result;
    }

    json_t *first_index_json_ptr = json_object_get(json_ptr, "firstIndex");
    if (json_is_null(first_index_json_ptr) || first_index_json_ptr == NULL) {
        result.validation_error = ERROR_FIRST_INDEX_MISSING;

        return result;
    }

    if (key_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_FIRST_INDEX_NOT_NUMBER;

        return result;
    }

    json_t *number_json_ptr = json_object_get(json_ptr, "number");
    if (json_is_null(number_json_ptr) || number_json_ptr == NULL) {
        result.validation_error = ERROR_NUMBER_MISSING;

        return result;
    }

    if (number_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_NUMBER_NOT_NUMBER;

        return result;
    }


    json_t *security_json_ptr = json_object_get(json_ptr, "security");
    if (json_is_null(security_json_ptr) || security_json_ptr == NULL) {
        result.validation_error = ERROR_SECURITY_MISSING;

        return result;
    }

    if (security_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_SECURITY_NOT_NUMBER;

        return result;
    }

    //Todo: Implement real UART communication
    result.tryte_array_ptr = json_string("AAAAAAA");

    return result;
}

void generate_address_handle_request(json_t *json_ptr, struct _u_response *response) {

    struct generate_address_validation_result result = generate_address_validation_result(json_ptr);

    if (result.successful) {
        uart_write(json_ptr);
        char * result = uart_read();
        ulfius_set_string_body_response(response, 200, result);
    } else {
        send_error_message(response, result.validation_error);
    }
}