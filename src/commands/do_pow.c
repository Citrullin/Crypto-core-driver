#include <stdbool.h>

#include <ulfius.h>
#include <uart.h>
#include "error_util.h"
#include "commands/do_pow.h"
#include "json_response_utils.h"

do_pow_validation_result_t do_pow_tangle_validate_json(json_t *json_ptr) {
    json_t *min_weight_magnitude_json_ptr = json_object_get(json_ptr, "minWeightMagnitude");

    if (json_is_null(min_weight_magnitude_json_ptr) || min_weight_magnitude_json_ptr == NULL) {
        do_pow_validation_result_t result = {.successful = false, .validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_MISSING};
        return result;
    }

    if (min_weight_magnitude_json_ptr->type != JSON_INTEGER) {
        do_pow_validation_result_t result = {.successful = false, .validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_NOT_INTEGER};
        return result;
    }

    json_t *trytes_ptr = json_object_get(json_ptr, "trytes");
    if (json_is_null(trytes_ptr) || trytes_ptr == NULL) {
        do_pow_validation_result_t result = {.successful = false, .validation_error = ERROR_MIN_WEIGHT_MAGNITUDE_MISSING};
        return result;
    }

    if (trytes_ptr->type != JSON_ARRAY) {
        do_pow_validation_result_t result = {.successful = false, .validation_error = ERROR_TRYTES_NOT_ARRAY};
        return result;
    }

    unsigned int i = 0;
    json_t *array_element_ptr;

    json_array_foreach(trytes_ptr, i, array_element_ptr) {
        if (array_element_ptr->type != JSON_STRING) {
            do_pow_validation_result_t result = {
                    .successful = false,
                    .validation_error = ERROR_TRYTES_ARRAY_NOT_STRING,
            };

            return result;
        }
    }


    do_pow_validation_result_t result = {
            .validation_error = true,
            .min_weight_magnitude = (uint8_t) json_number_value(min_weight_magnitude_json_ptr),
            .trytes = trytes_ptr,
    };

    return result;
}

void set_do_pow_error_message(json_t *response_obj_json, do_pow_validation_result_t * result){
    if (result->validation_error == ERROR_MIN_WEIGHT_MAGNITUDE_MISSING) {
        char message[] = MIN_WEIGHT_MAGNITUDE_MISSING_MESSAGE;
        json_response_set_error_message(response_obj_json, message);
    }
    else if (result->validation_error == ERROR_MIN_WEIGHT_MAGNITUDE_NOT_INTEGER) {
        char message[] = MIN_WEIGHT_MAGNITUDE_NOT_INTEGER_MESSAGE;
        json_response_set_error_message(response_obj_json, message);
    }
    else if (result->validation_error == ERROR_TRYTES_MISSING) {
        char message[] = TRYTES_MISSING_MESSAGE;
        json_response_set_error_message(response_obj_json, message);
    }
    else if (result->validation_error == ERROR_TRYTES_NOT_ARRAY) {
        char message[] = TRYYES_NOT_ARRAY_MESSAGE;
        json_response_set_error_message(response_obj_json, message);
    }
}

void do_pow_handle_request(json_t *json_ptr, struct _u_response *response) {
    json_t *response_obj_json = json_object();

    do_pow_validation_result_t result = do_pow_tangle_validate_json(json_ptr);

    if (result.successful) {
        uart_write(json_ptr);
        char * result = uart_read();
        ulfius_set_string_body_response(response, 200, result);
    } else {
        set_do_pow_error_message(response_obj_json, &result);
    }

    ulfius_set_json_body_response(response, 400, response_obj_json);
}