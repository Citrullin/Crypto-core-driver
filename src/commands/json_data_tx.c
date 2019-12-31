#include <ulfius.h>
#include <stdbool.h>
#include <error_util.h>
#include <uart.h>
#include <string.h>

struct json_data_tx_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *trunk_transaction;
    json_t *branch_transaction;
    json_t *min_weight_magnitude;
    json_t *tag;
    json_t *address;
    json_t *timestamp;
    json_t *data;
};

struct json_data_tx_validation_result json_data_tx_validate_json(json_t *json_ptr){
    struct json_data_tx_validation_result result = {.successful = false};

    json_t *trunk_transaction_json_ptr = json_object_get(json_ptr, "trunkTransaction");
    if (json_is_null(trunk_transaction_json_ptr) || trunk_transaction_json_ptr == NULL) {
        result.validation_error = ERROR_TRUNK_TRANSACTION_MISSING;
    }

    if (trunk_transaction_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_TRUNK_TRANSACTION_NOT_STRING;
    }

    const char * trunk_transaction_ptr = json_string_value(trunk_transaction_json_ptr);
    if(strlen(trunk_transaction_ptr) != 81){
        result.validation_error = ERROR_TRUNK_TRANSACTION_WRONG_SIZE;
    }

    json_t *branch_transaction_json_ptr = json_object_get(json_ptr, "branchTransaction");
    if (json_is_null(branch_transaction_json_ptr) || branch_transaction_json_ptr == NULL) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_MISSING;
    }

    if (branch_transaction_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_NOT_STRING;
    }

    const char * branch_transaction_ptr = json_string_value(branch_transaction_json_ptr);
    if(strlen(branch_transaction_ptr) != 81){
        result.validation_error = ERROR_TRUNK_TRANSACTION_WRONG_SIZE;
    }

    json_t *min_weight_magnitude_json_ptr = json_object_get(json_ptr, "minWeightMagnitude");
    if (json_is_null(min_weight_magnitude_json_ptr) || min_weight_magnitude_json_ptr == NULL) {
        result.validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_MISSING;
    }

    if (min_weight_magnitude_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER;
    }

    json_t *address_json_ptr = json_object_get(json_ptr, "address");
    if (json_is_null(address_json_ptr) || address_json_ptr == NULL) {
        result.validation_error = ERROR_ADDRESS_MISSING;
    }

    if (address_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_ADDRESS_NOT_STRING;
    }

    const char * address_ptr = json_string_value(address_json_ptr);
    if(strlen(address_ptr) != 81){
        result.validation_error = ERROR_ADDRESS_WRONG_SIZE;
    }

    json_t *tag_json_ptr = json_object_get(json_ptr, "tag");
    if (json_is_null(tag_json_ptr) || tag_json_ptr == NULL) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_MISSING;
    }

    if (tag_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_BRANCH_TRANSACTION_NOT_STRING;
    }

    const char * tag_ptr = json_string_value(tag_json_ptr);
    if(strlen(tag_ptr) != 27){
        result.validation_error = ERROR_TAG_WRONG_SIZE;
    }

    json_t *timestamp_json_ptr = json_object_get(json_ptr, "timestamp");
    if (json_is_null(timestamp_json_ptr) || timestamp_json_ptr == NULL) {
        result.validation_error = ERROR_TIMESTAMP_MISSING;
    }

    if (timestamp_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_TIMESTAMP_NOT_NUMBER;
    }

    result.successful = true;
    result.address = address_json_ptr;
    result.branch_transaction = branch_transaction_json_ptr;
    result.trunk_transaction = trunk_transaction_json_ptr;
    result.data = json_object_get(json_ptr, "data");
    result.tag = tag_json_ptr;
    result.min_weight_magnitude = min_weight_magnitude_json_ptr;
    result.timestamp = timestamp_json_ptr;

    return result;
}

void json_data_tx_handle_request(json_t *json_ptr, struct _u_response *response) {
    struct json_data_tx_validation_result validation_result = json_data_tx_validate_json(json_ptr);

    if (validation_result.successful) {
        uart_write(json_ptr);
        char * result = uart_read();
        ulfius_set_string_body_response(response, 200, result);
    } else {
        send_error_message(response, validation_result.validation_error);
    }
}


