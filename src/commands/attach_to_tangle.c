#include <string.h>
#include <stdbool.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <ulfius.h>

#include "../include/error_util.h"

#include "include/attach_to_tangle.h"
#include "../include/json_response_utils.h"

struct attach_to_tangle_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *trunk_transaction_ptr;
    json_t *branch_transaction_ptr;
    uint8_t min_weight_magnitude;
    uint32_t timestamp;
    json_t *tryte_array_ptr;
};

struct attach_to_tangle_validation_result attach_to_tangle_validate_json(json_t *json_ptr) {

    json_t *trunk_transaction_json_ptr = json_object_get(json_ptr, "trunkTransaction");
    if (json_is_null(trunk_transaction_json_ptr) || trunk_transaction_json_ptr == NULL) {
        struct attach_to_tangle_validation_result result = {
            .successful = false,
            .validation_error = ERROR_TRUNK_TRANSACTION_MISSING
        };
        return result;
    }

    if (trunk_transaction_json_ptr->type != JSON_STRING) {
        struct attach_to_tangle_validation_result result = {
            .successful = false,
            .validation_error = ERROR_TRUNK_TRANSACTION_NOT_STRING
        };
        return result;
    }

    json_t *branch_transaction_json_ptr = json_object_get(json_ptr, "branchTransaction");
    if (json_is_null(branch_transaction_json_ptr) || branch_transaction_json_ptr == NULL) {
        struct attach_to_tangle_validation_result result = {
            .successful = false,
            .validation_error = ERROR_BRANCH_TRANSACTION_MISSING
        };
        return result;
    }

    if (branch_transaction_json_ptr->type != JSON_STRING) {
        struct attach_to_tangle_validation_result result = {
            .successful = false,
            .validation_error = ERROR_BRANCH_TRANSACTION_NOT_STRING
        };
        return result;
    }

    json_t *min_weight_magnitude_json_ptr = json_object_get(json_ptr, "minWeightMagnitude");
    if (json_is_null(min_weight_magnitude_json_ptr) || min_weight_magnitude_json_ptr == NULL) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_MISSING};
        return result;
    }

    if (min_weight_magnitude_json_ptr->type != JSON_INTEGER) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER};
        return result;
    }

    json_t *timestamp_json_ptr = json_object_get(json_ptr, "timestamp");
    if (json_is_null(timestamp_json_ptr) || timestamp_json_ptr == NULL) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_TIMESTAMP_MISSING};
        return result;
    }

    if (timestamp_json_ptr->type != JSON_INTEGER) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_TIMESTAMP_NOT_NUMBER};
        return result;
    }

    json_t *trytes_json_ptr = json_object_get(json_ptr, "trytes");
    if (json_is_null(trytes_json_ptr) || trytes_json_ptr == NULL) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_TRYTES_MISSING};
        return result;
    }

    if (trytes_json_ptr->type != JSON_ARRAY) {
        struct attach_to_tangle_validation_result result =
            {.successful = false, .validation_error = ERROR_TRYTES_NOT_ARRAY};
        return result;
    }

    struct attach_to_tangle_validation_result result =
        {
            .successful = true,
            .trunk_transaction_ptr = trunk_transaction_json_ptr,
            .branch_transaction_ptr = branch_transaction_json_ptr,
            .timestamp = (uint32_t) json_number_value(timestamp_json_ptr),
            .min_weight_magnitude = (uint32_t) json_number_value(min_weight_magnitude_json_ptr),
            .tryte_array_ptr = trytes_json_ptr,
        };
    return result;
}

void attach_to_tangle_handle_request(json_t *json_ptr, struct _u_response *response) {
    json_t *response_obj_json = json_object();

    struct attach_to_tangle_validation_result result = attach_to_tangle_validate_json(json_ptr);

    if (result.successful) {
        ulfius_set_string_body_response(response, 200, "attachToTangle");
    } else {
        if (result.validation_error == ERROR_TRUNK_TRANSACTION_MISSING) {
            char message[] = TRUNK_TRANSACTION_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_BRANCH_TRANSACTION_MISSING) {
            char message[] = BRANCH_TRANSACTION_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_MIN_WEIGHT_MAGNITUDE_MISSING) {
            char message[] = MIN_WEIGHT_MAGNITUDE_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_TIMESTAMP_MISSING) {
            char message[] = TIMESTAMP_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_TRYTES_MISSING) {
            char message[] = TRYTES_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_TRYTES_NOT_ARRAY) {
            char message[] = TRYTES_NOT_ARRAY_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_TIMESTAMP_NOT_NUMBER) {
            char message[] = TIMESTAMP_NOT_NUMBER_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER) {
            char message[] = MIN_WEIGHT_MAGNITUDE_NOT_NUMBER_MESAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_BRANCH_TRANSACTION_NOT_STRING) {
            char message[] = BRANCH_TRANSACTION_NOT_STRING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }
        else if (result.validation_error == ERROR_TRUNK_TRANSACTION_NOT_STRING) {
            char message[] = TRUNK_TRANSACTION_NOT_STRING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }

        ulfius_set_json_body_response(response, 400, response_obj_json);
    }
}