#include <ulfius.h>

struct sign_transaction_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *key_ptr;
    json_t *address_index;
    json_t *bundle_hash;
    json_t *security_level;
    json_t *auth;
};

struct sign_transaction_validation_result sign_transaction_validate_json(json_t *json_ptr){
    struct sign_transaction_validation_result result = {.successful = false};

    json_t *key_json_ptr = json_object_get(json_ptr, "key");
    if (json_is_null(key_json_ptr) || key_json_ptr == NULL) {
        result.validation_error = ERROR_KEY_MISSING;
        return result;
    }

    if (key_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ERROR_KEY_NOT_NUMBER;
        return result;
    }

    json_t *address_index_json_ptr = json_object_get(json_ptr, "addressIndex");
    if (json_is_null(address_index_json_ptr) || address_index_json_ptr == NULL) {
        result.validation_error = ADDRESS_INDEX_MISSING_MESSAGE;
        return result;
    }

    if (address_index_json_ptr->type != JSON_INTEGER) {
        result.validation_error = ADDRESS_INDEX_NOT_NUMBER;
        return result;
    }

    json_t *bundle_hash_json_ptr = json_object_get(json_ptr, "bundleHash");
    if (json_is_null(bundle_hash_json_ptr) || bundle_hash_json_ptr == NULL) {
        result.validation_error = ERROR_BUNDLE_HASH_MISSING;
        return result;
    }

    if (address_index_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_BUNDLE_HASH_NOT_STRING;
        return result;
    }

    json_t *security_level_json_ptr = json_object_get(json_ptr, "securityLevel");
    if (json_is_null(security_level_json_ptr) || security_level_json_ptr == NULL) {
        result.validation_error = SECURITY_LEVEL_MISSING_MESSAGE;
        return result;
    }

    if (address_index_json_ptr->type != JSON_STRING) {
        result.validation_error = ERROR_BUNDLE_HASH_NOT_STRING;
        return result;
    }

    json_t *auth_json_ptr = json_object_get(json_ptr, "auth");
    if (json_is_null(auth_json_ptr) || auth_json_ptr == NULL) {
        result.validation_error = AUTH_MISSING_MESSAGE;
        return result;
    }

    if (address_index_json_ptr->type != JSON_STRING) {
        result.validation_error = AUTH_NOT_STRING;
        return result;
    }

    result.successful = true;
    result.key_ptr = key_json_ptr;
    result.address_index = address_index_json_ptr;
    result.bundle_hash = bundle_hash_json_ptr;
    result.auth = auth_json_ptr;
    result.security_level = security_level_json_ptr;

    return result;
}

void sign_transaction_handle_request(json_t *json_ptr, struct _u_response *response) {
    struct sign_transaction_validation_result validation_result = sign_transaction_validate_json(json_ptr);

    if (validation_result.successful) {
        //Todo: Implement UART and response
        ulfius_set_string_body_response(response, 200, "signTransaction");
    } else {
        send_error_message(response, validation_result.validation_error);
    }
}