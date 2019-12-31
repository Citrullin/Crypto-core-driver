#include <string.h>
#include <stdbool.h>

#ifndef _WIN32

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <ulfius.h>

#include "config.h"
#include "callbacks.h"

#include "commands/attach_to_tangle.h"
#include "commands/do_pow.h"
#include "commands/generate_address.h"
#include "commands/generate_random_seed.h"
#include "commands/set_flags.h"
#include "commands/sign_transaction.h"
#include "commands/test_hardware_acceleration.h"
#include "commands/json_data_tx.h"


#define IOTA_API_VERSION_HEADER_KEY "X-IOTA-API-Version"
#define SUPPORTED_IOTA_API_VERSION 1

#define CONTENT_TYPE_KEY "Content-Type"
#define CONTENT_TYPE_VALUE "application/json"

#define CMD_ATTACH_TO_TANGLE "attachToTangle"
#define CMD_SET_FLAGS "setFlags"
#define CMD_TEST_HARDWARE "testHardwareAcceleration"
#define CMD_GENERATE_RANDOM_SEED "generateRandomSeed"
#define CMD_GENERATE_ADDRESS "generateAddress"
#define CMD_DO_POW "doPow"
#define CMD_SIGN_TRANSACTION "signTransaction"
#define CMD_JSON_DATA_TX "jsonDataTX"

#define CONTENT_TYPE_NOT_PROVIDED_MESSAGE "Content-Type not provided."
#define CONTENT_TYPE_NOT_JSON_MESSAGE "Content-Type is not application/json."

#define API_VERSION_NOT_SUPPORTED_MESSAGE "The given X-IOTA-API-Version is not supported."
#define API_VERSION_NOT_GIVEN_MESSAGE "X-IOTA-API-Version not given. Please provide API version."

#define COMMAND_DOES_NOT_EXIST_MESSAGE "The given command does not exist."

#define JSON_NOT_OBJ_MESSAGE "The given json is not an object."
#define JSON_NOT_GIVEN_MESSAGE "Please provide a json object body."

#define COMMAND_EMPTY_MESSAGE "The command is empty or not given."
#define COMMAND_NOT_STRING_MESSAGE "The command is not a string."

bool api_version_validation(const struct _u_request *request, struct _u_response *response) {
    if (u_map_has_key(request->map_header, IOTA_API_VERSION_HEADER_KEY)) {
        unsigned int version = atoi(u_map_get(request->map_header, IOTA_API_VERSION_HEADER_KEY));
        if (version <= SUPPORTED_IOTA_API_VERSION) {
            return true;
        } else {
            json_t *response_obj_json = json_object();
            char message[] = API_VERSION_NOT_SUPPORTED_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);

            return false;
        }
    } else {
        json_t *response_obj_json = json_object();
        char message[] = API_VERSION_NOT_GIVEN_MESSAGE;
        json_t *response_message_json = json_string(message);
        json_object_set_new(response_obj_json, "message", response_message_json);

        ulfius_set_json_body_response(response, 400, response_obj_json);

        return false;
    }
}

bool content_type_validation(const struct _u_request *request, struct _u_response *response) {
    if (u_map_has_key(request->map_header, CONTENT_TYPE_KEY)) {
        const char *content_type = u_map_get(request->map_header, CONTENT_TYPE_KEY);
        if (strcmp(CONTENT_TYPE_VALUE, content_type) == 0) {
            return true;
        } else {
            json_t *response_obj_json = json_object();
            char message[] = CONTENT_TYPE_NOT_JSON_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);

            return false;
        }
    } else {
        json_t *response_obj_json = json_object();
        char message[] = CONTENT_TYPE_NOT_PROVIDED_MESSAGE;
        json_t *response_message_json = json_string(message);
        json_object_set_new(response_obj_json, "message", response_message_json);

        ulfius_set_json_body_response(response, 400, response_obj_json);

        return false;
    }
}

bool validate_json_structure(json_t *json_ptr, struct _u_response *response) {
    if (json_is_object(json_ptr)) {
        json_t *command_json_ptr = json_object_get(json_ptr, "command");

        if (json_is_null(command_json_ptr) || command_json_ptr == NULL) {
            json_t *response_obj_json = json_object();
            char message[] = COMMAND_EMPTY_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);

            return false;
        } else if (!json_is_string(command_json_ptr)) {
            json_t *response_obj_json = json_object();
            char message[] = COMMAND_NOT_STRING_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);

            return false;
        }

        return true;
    } else {
        json_t *response_obj_json = json_object();
        char message[] = JSON_NOT_OBJ_MESSAGE;
        json_t *response_message_json = json_string(message);
        json_object_set_new(response_obj_json, "message", response_message_json);

        ulfius_set_json_body_response(response, 400, response_obj_json);

        return false;
    }
}

const char *get_command_value(json_t *json_ptr) {
    json_t *command_json_ptr = json_object_get(json_ptr, "command");
    return json_string_value(command_json_ptr);
}

void handle_api_request(json_t *json_ptr, struct _u_response *response) {
    if (validate_json_structure(json_ptr, response)) {
        const char *command = get_command_value(json_ptr);

        if (strcmp(CMD_ATTACH_TO_TANGLE, command) == 0) {
            attach_to_tangle_handle_request(json_ptr, response);
        } else if (strcmp(CMD_DO_POW, command) == 0) {
            do_pow_handle_request(json_ptr, response);
        } else if (strcmp(CMD_GENERATE_ADDRESS, command) == 0) {
            generate_address_handle_request(json_ptr, response);
        } else if (strcmp(CMD_GENERATE_RANDOM_SEED, command) == 0) {
            generate_random_seed_handle_request(json_ptr, response);
        } else if (strcmp(CMD_SIGN_TRANSACTION, command) == 0) {
            sign_transaction_handle_request(json_ptr, response);
        } else if (strcmp(CMD_TEST_HARDWARE, command) == 0) {
            test_hardware_acceleration_handle_request(json_ptr, response);
        } else if (strcmp(CMD_SET_FLAGS, command) == 0) {
            set_flags_handle_request(json_ptr, response);
        }else if (strcmp(CMD_JSON_DATA_TX, command) == 0){
            json_data_tx_handle_request(json_ptr, response);
        } else {
            json_t *response_obj_json = json_object();
            char message[] = COMMAND_DOES_NOT_EXIST_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);
        }
    }
}

int callback_api(const struct _u_request *request, struct _u_response *response, void *user_data) {

    if (api_version_validation(request, response) && content_type_validation(request, response)) {
        json_error_t *json_error_ptr = {0};
        json_t *json_ptr = ulfius_get_json_body_request(request, json_error_ptr);

        if (json_is_null(json_ptr) || json_ptr == NULL) {
            json_t *response_obj_json = json_object();
            char message[] = JSON_NOT_GIVEN_MESSAGE;
            json_t *response_message_json = json_string(message);
            json_object_set_new(response_obj_json, "message", response_message_json);

            ulfius_set_json_body_response(response, 400, response_obj_json);
        } else {
            handle_api_request(json_ptr, response);
        }
    }
    return U_CALLBACK_CONTINUE;
}

int callback_not_found(const struct _u_request *request, struct _u_response *response, void *user_data) {
    ulfius_set_string_body_response(response, 404, "Page not found");
    return U_CALLBACK_CONTINUE;
}