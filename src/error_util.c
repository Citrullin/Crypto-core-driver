#include <string.h>
#include <ulfius.h>
#include "error_util.h"

char error_message_buffer[100];
void send_error_message(struct _u_response *response, crypto_core_json_validation_error_t validation_error){
    json_t *response_obj_json = json_object();

    switch(validation_error){
        case ERROR_MIN_WEIGHT_MAGNITUDE_MISSING:
            strcpy(error_message_buffer, MIN_WEIGHT_MAGNITUDE_MISSING_MESSAGE);
            break;
        case ERROR_MIN_WEIGHT_MAGNITUDE_NOT_INTEGER:
            strcpy(error_message_buffer, MIN_WEIGHT_MAGNITUDE_NOT_NUMBER_MESAGE);
            break;
        case ERROR_TRYTES_MISSING:
            strcpy(error_message_buffer, TRYTES_MISSING_MESSAGE);
            break;
        case ERROR_TRYTES_NOT_ARRAY:
            strcpy(error_message_buffer, TRYTES_NOT_ARRAY_MESSAGE);
            break;
        case ERROR_TRYTES_ARRAY_NOT_STRING:
            strcpy(error_message_buffer, TRYTES_ARRAY_NOT_STRING_MESSAGE);
            break;
        case ERROR_MISSING_FLAGS:
            strcpy(error_message_buffer, FLAGS_MISSING_MESSAGE);
            break;
        case ERROR_FLAGS_NOT_OBJECT:
            strcpy(error_message_buffer, FLAGS_IS_NOT_OBJECT_MESSAGE);
            break;
        case ERROR_KEEP_SEED_IN_RAM_MISSING:
            strcpy(error_message_buffer, KEEP_SEED_IN_RAM_MISSING_MESSAGE);
            break;
        case ERROR_KEEP_SEED_IN_RAM_NOT_BOOL:
            strcpy(error_message_buffer, KEEP_SEED_IN_RAM_NOT_BOOL_MESSAGE);
            break;
        case ERROR_TRUNK_TRANSACTION_MISSING:
            strcpy(error_message_buffer, TRUNK_TRANSACTION_MISSING_MESSAGE);
            break;
        case ERROR_TRUNK_TRANSACTION_NOT_STRING:
            strcpy(error_message_buffer, TRUNK_TRANSACTION_NOT_STRING_MESSAGE);
            break;
        case ERROR_BRANCH_TRANSACTION_MISSING:
            strcpy(error_message_buffer, BRANCH_TRANSACTION_MISSING_MESSAGE);
            break;
        case ERROR_BRANCH_TRANSACTION_NOT_STRING:
            strcpy(error_message_buffer, BRANCH_TRANSACTION_NOT_STRING_MESSAGE);
            break;
        case ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER:
            strcpy(error_message_buffer, MIN_WEIGHT_MAGNITUDE_NOT_NUMBER_MESAGE);
            break;
        case ERROR_TIMESTAMP_MISSING:
            strcpy(error_message_buffer, TIMESTAMP_MISSING_MESSAGE);
            break;
        case ERROR_TIMESTAMP_NOT_NUMBER:
            strcpy(error_message_buffer, TIMESTAMP_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_KEY_MISSING:
            strcpy(error_message_buffer, KEY_MISSING_MESSAGE);
            break;
        case ERROR_KEY_NOT_NUMBER:
            strcpy(error_message_buffer, KEY_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_FIRST_INDEX_MISSING:
            strcpy(error_message_buffer, FIRST_INDEX_MISSING_MESSAGE);
            break;
        case ERROR_FIRST_INDEX_NOT_NUMBER:
            strcpy(error_message_buffer, FIRST_INDEX_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_NUMBER_MISSING:
            strcpy(error_message_buffer, NUMBER_MISSING_MESSAGE);
            break;
        case ERROR_NUMBER_NOT_NUMBER:
            strcpy(error_message_buffer, NUMBER_NOT_NUMBER);
            break;
        case ERROR_SECURITY_MISSING:
            strcpy(error_message_buffer, SECURITY_MISSING_MESSAGE);
            break;
        case ERROR_SECURITY_NOT_NUMBER:
            strcpy(error_message_buffer, SECURITY_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_BUNDLE_HASH_MISSING:
            strcpy(error_message_buffer, BUNDLE_HASH_MISSING_MESSAGE);
            break;
        case ERROR_BUNDLE_HASH_NOT_STRING:
            strcpy(error_message_buffer, BUNDLE_HASH_NOT_STRING_MESSAGE);
            break;
        case ERROR_SECURITY_LEVEL_MISSING:
            strcpy(error_message_buffer, SECURITY_LEVEL_MISSING_MESSAGE);
            break;
        case ERROR_SECURITY_LEVEL_NOT_NUMBER:
            strcpy(error_message_buffer, SECURITY_LEVEL_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_ADDRESS_INDEX_MISSING:
            strcpy(error_message_buffer, ADDRESS_INDEX_MISSING_MESSAGE);
            break;
        case ERROR_AUTH_MISSING:
            strcpy(error_message_buffer, AUTH_NOT_STRING_MESSAGE);
            break;
        case ERROR_ADDRESS_INDEX_NOT_NUMBER:
            strcpy(error_message_buffer, ADDRESS_INDEX_NOT_NUMBER_MESSAGE);
            break;
        case ERROR_AUTH_NOT_STRING:
            strcpy(error_message_buffer, AUTH_NOT_STRING_MESSAGE);
            break;
    }

    ulfius_set_json_body_response(response, 400, response_obj_json);
}
