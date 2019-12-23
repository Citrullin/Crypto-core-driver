#include <ulfius.h>

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

    if (min_weight_magnitude_json_ptr->type != JSON_NUMBER) {
        result.validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER;
        return result;
    }

}


