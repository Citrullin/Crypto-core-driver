#include <string.h>
#include <stdbool.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <termios.h>

#endif

#include <ulfius.h>
#include <uart.h>

#include "error_util.h"

#include "commands/attach_to_tangle.h"
#include "json_response_utils.h"

struct attach_to_tangle_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *trunk_transaction_ptr;
    json_t *branch_transaction_ptr;
    uint8_t min_weight_magnitude;
    uint32_t timestamp;
    json_t *tryte_array_ptr;
};

void init_uart(){

}

struct attach_to_tangle_validation_result attach_to_tangle_validate_json(json_t *json_ptr) {
    struct attach_to_tangle_validation_result result = {.successful = false};

    json_t *trunk_transaction_json_ptr = json_object_get(json_ptr, "trunkTransaction");
    if (json_is_null(trunk_transaction_json_ptr) || trunk_transaction_json_ptr == NULL) {
        result.validation_error = ERROR_TRUNK_TRANSACTION_MISSING;

        return result;
    }

    if (trunk_transaction_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_TRUNK_TRANSACTION_NOT_STRING;

        return result;
    }

    json_t *branch_transaction_json_ptr = json_object_get(json_ptr, "branchTransaction");
    if (json_is_null(branch_transaction_json_ptr) || branch_transaction_json_ptr == NULL) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_MISSING;

        return result;
    }

    if (branch_transaction_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_NOT_STRING;

        return result;
    }

    json_t *min_weight_magnitude_json_ptr = json_object_get(json_ptr, "minWeightMagnitude");
    if (json_is_null(min_weight_magnitude_json_ptr) || min_weight_magnitude_json_ptr == NULL) {
        result.validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_MISSING;

        return result;
    }

    if (min_weight_magnitude_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER;

        return result;
    }

    json_t *timestamp_json_ptr = json_object_get(json_ptr, "timestamp");
    if (json_is_null(timestamp_json_ptr) || timestamp_json_ptr == NULL) {
        result.validation_error = ERROR_TIMESTAMP_MISSING;

        return result;
    }

    if (timestamp_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_TIMESTAMP_NOT_NUMBER;

        return result;
    }

    json_t *trytes_json_ptr = json_object_get(json_ptr, "trytes");
    if (json_is_null(trytes_json_ptr) || trytes_json_ptr == NULL) {
        result.validation_error = ERROR_TRYTES_MISSING;

        return result;
    }

    if (trytes_json_ptr->type != JSON_ARRAY) {
        result.validation_error = ERROR_TRYTES_NOT_ARRAY;

        return result;
    }

    result.successful = true;
    result.trunk_transaction_ptr = trunk_transaction_json_ptr;
    result.branch_transaction_ptr = branch_transaction_json_ptr;
    result.timestamp = (uint32_t) json_number_value(timestamp_json_ptr);
    result.min_weight_magnitude = (uint32_t) json_number_value(min_weight_magnitude_json_ptr);
    result.tryte_array_ptr = trytes_json_ptr;

    return result;
}

void attach_to_tangle_handle_request(json_t *json_ptr, struct _u_response *response) {

    struct attach_to_tangle_validation_result validation_result = attach_to_tangle_validate_json(json_ptr);

    if (validation_result.successful) {
        //Todo: Implement UART and response
        uart_write(json_ptr);
        char * result = uart_read();
        ulfius_set_string_body_response(response, 200, result);
    } else {
        send_error_message(response, validation_result.validation_error);
    }
}