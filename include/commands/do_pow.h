#ifndef ULFIUS_DO_POW_H
#define ULFIUS_DO_POW_H

#include <ulfius.h>
#include "error_util.h"

typedef struct {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    uint8_t min_weight_magnitude;
    json_t *trytes;
} do_pow_validation_result_t;

void set_do_pow_error_message(json_t *response_obj_json, do_pow_validation_result_t * result);

void do_pow_handle_request(json_t *json_ptr, struct _u_response *response);

#endif //ULFIUS_DO_POW_H
