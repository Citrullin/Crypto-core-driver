#include <string.h>
#include <stdbool.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <ulfius.h>

#include "error_util.h"

#include "json_response_utils.h"

struct set_flags_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    bool keep_seed_in_memory;
};

struct set_flags_validation_result set_flags_validate_json(json_t *json_ptr) {
    json_t *flags_json_ptr = json_object_get(json_ptr, "flags");

    if (json_is_null(flags_json_ptr) || flags_json_ptr == NULL) {
        struct set_flags_validation_result result = {.successful = false, .validation_error = ERROR_MISSING_FLAGS};
        return result;
    }

    if (!json_is_object(flags_json_ptr)) {
        struct set_flags_validation_result result = {.successful = false, .validation_error = ERROR_FLAGS_NOT_OBJECT};
        return result;
    }

    json_t *keep_seed_in_ram_json_ptr = json_object_get(flags_json_ptr, "keepSeedInRAM");

    if (json_is_null(keep_seed_in_ram_json_ptr) || keep_seed_in_ram_json_ptr == NULL) {
        struct set_flags_validation_result result =
                {.successful = false, .validation_error = ERROR_KEEP_SEED_IN_RAM_MISSING};
        return result;
    }

    if (!json_is_boolean(keep_seed_in_ram_json_ptr)) {
        struct set_flags_validation_result result =
                {.successful = false, .validation_error = ERROR_KEEP_SEED_IN_RAM_NOT_BOOL};
        return result;
    }

    struct set_flags_validation_result result =
            {.successful = true, .keep_seed_in_memory = json_boolean(keep_seed_in_ram_json_ptr)};
    return result;
}

void set_flags_handle_request(json_t *json_ptr, struct _u_response *response) {
    json_t *response_obj_json = json_object();
    struct set_flags_validation_result validation_result = set_flags_validate_json(json_ptr);

    if (validation_result.successful) {
        char message[] = SET_FLAGS_SUCCESSFUL_MESSAGE;
        json_t *response_message_json = json_string(message);
        json_object_set_new(response_obj_json, "message", response_message_json);

        ulfius_set_json_body_response(response, 200, response_obj_json);
    } else {
        if (validation_result.validation_error == ERROR_MISSING_FLAGS) {
            char message[] = FLAGS_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        } else if (validation_result.validation_error == ERROR_FLAGS_NOT_OBJECT) {
            char message[] = FLAGS_IS_NOT_OBJECT_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        } else if (validation_result.validation_error == ERROR_KEEP_SEED_IN_RAM_MISSING) {
            char message[] = KEEP_SEED_IN_RAM_MISSING_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        } else if (validation_result.validation_error == ERROR_KEEP_SEED_IN_RAM_NOT_BOOL) {
            char message[] = KEEP_SEED_IN_RAM_NOT_BOOL_MESSAGE;
            json_response_set_error_message(response_obj_json, message);
        }

        ulfius_set_json_body_response(response, 400, response_obj_json);
    }
}