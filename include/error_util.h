#ifndef CRYPTO_CORE_ERROR_UTIL_H
#define CRYPTO_CORE_ERROR_UTIL_H

typedef enum {
    ERROR_MIN_WEIGHT_MAGNITUDE_MISSING,
    //fixme: dublicate
    ERROR_MIN_WEIGHT_MAGNITUDE_NOT_INTEGER,
    ERROR_TRYTES_MISSING,
    ERROR_TRYTES_NOT_ARRAY,
    ERROR_TRYTES_ARRAY_NOT_STRING,
    ERROR_MISSING_FLAGS,
    ERROR_FLAGS_NOT_OBJECT,
    ERROR_KEEP_SEED_IN_RAM_MISSING,
    ERROR_KEEP_SEED_IN_RAM_NOT_BOOL,
    ERROR_TRUNK_TRANSACTION_MISSING,
    ERROR_TRUNK_TRANSACTION_NOT_STRING,
    ERROR_TRUNK_TRANSACTION_WRONG_SIZE,
    ERROR_BRANCH_TRANSACTION_MISSING,
    ERROR_BRANCH_TRANSACTION_NOT_STRING,
    ERROR_BRANCH_TRANSACTION_WRONG_SIZE,
    ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER,
    ERROR_TIMESTAMP_MISSING,
    ERROR_TIMESTAMP_NOT_NUMBER,
    ERROR_KEY_MISSING,
    ERROR_KEY_NOT_NUMBER,
    ERROR_FIRST_INDEX_MISSING,
    ERROR_FIRST_INDEX_NOT_NUMBER,
    ERROR_NUMBER_MISSING,
    ERROR_NUMBER_NOT_NUMBER,
    ERROR_SECURITY_MISSING,
    ERROR_SECURITY_NOT_NUMBER,
    //Todo: Consistency security vs. securityLevel
    ERROR_SECURITY_LEVEL_MISSING,
    ERROR_SECURITY_LEVEL_NOT_NUMBER,
    ERROR_ADDRESS_INDEX_MISSING,
    ERROR_ADDRESS_INDEX_NOT_NUMBER,
    ERROR_ADDRESS_MISSING,
    ERROR_ADDRESS_NOT_STRING,
    ERROR_ADDRESS_WRONG_SIZE,
    ERROR_BUNDLE_HASH_MISSING,
    ERROR_BUNDLE_HASH_NOT_STRING,
    ERROR_AUTH_MISSING,
    ERROR_AUTH_NOT_STRING,
    ERROR_TAG_WRONG_SIZE
} crypto_core_json_validation_error_t;

void send_error_message(struct _u_response *response, crypto_core_json_validation_error_t validation_error);

#define SET_FLAGS_SUCCESSFUL_MESSAGE "Configuration of flags was successful."
#define SET_FLAGS_JSON_STRUCTURE_INVALID "The given json structure for the setFlags command is invalid."
#define FLAGS_MISSING_MESSAGE "The flags property is missing."
#define FLAGS_IS_NOT_OBJECT_MESSAGE "The flags property is not an object."
#define KEEP_SEED_IN_RAM_MISSING_MESSAGE "The keepSeedInRAM property is missing."
#define KEEP_SEED_IN_RAM_EMPTY_MESSAGE "keepSeedInRAM property is empty."
#define KEEP_SEED_IN_RAM_NOT_BOOL_MESSAGE "keepSeedInRAM property is not a bool."
#define MIN_WEIGHT_MAGNITUDE_MISSING_MESSAGE "The property minWeightMagnitude is missing."
#define MIN_WEIGHT_MAGNITUDE_NOT_INTEGER_MESSAGE "The property minWeightMagnitude is not an integer."
#define TRYYES_NOT_ARRAY_MESSAGE "The property trytes is not an array."
#define TRYTES_ARRAY_NOT_STRING_MESSAGE "The property trytes must contain only strings."
#define TRUNK_TRANSACTION_MISSING_MESSAGE "trunkTransaction property is missing."
#define TRUNK_TRANSACTION_NOT_STRING_MESSAGE "trunkTransaction is not a string."
#define BRANCH_TRANSACTION_MISSING_MESSAGE "branchTransaction property is missing."
#define BRANCH_TRANSACTION_NOT_STRING_MESSAGE "branchTransaction is not a string."
#define MIN_WEIGHT_MAGNITUDE_NOT_NUMBER_MESAGE "minWeightMagnitude is not a number."
#define TIMESTAMP_MISSING_MESSAGE "timestamp property is missing."
#define TIMESTAMP_NOT_NUMBER_MESSAGE "timestamp is not an integer."
#define TRYTES_MISSING_MESSAGE "trytes property is missing."
#define TRYTES_NOT_ARRAY_MESSAGE "trytes is not an array."
//fixme
#define KEY_MISSING_MESSAGE "Key is missing"
#define KEY_NOT_NUMBER_MESSAGE "Key is not a number"
#define FIRST_INDEX_MISSING_MESSAGE "The first index is missing"
#define FIRST_INDEX_NOT_NUMBER_MESSAGE "First index not a number"
#define NUMBER_MISSING_MESSAGE "number is missing"
#define NUMBER_NOT_NUMBER "the property number is not a json number"
#define SECURITY_MISSING_MESSAGE "Security is missing"
#define SECURITY_NOT_NUMBER_MESSAGE "Security is not a number"
#define SECURITY_LEVEL_MISSING_MESSAGE "Security level is missing"
#define SECURITY_LEVEL_NOT_NUMBER_MESSAGE "Security level is not a number"
#define ADDRESS_INDEX_MISSING_MESSAGE "Address index is missing"
#define ADDRESS_INDEX_NOT_NUMBER_MESSAGE "Address is not a number"
#define BUNDLE_HASH_MISSING_MESSAGE "Bundle hash is missing"
#define BUNDLE_HASH_NOT_STRING_MESSAGE "Bundle hash is not a string"
#define AUTH_MISSING_MESSAGE "Auth missing"
#define AUTH_NOT_STRING_MESSAGE "Auth is not a string"
#define TRUNK_TRANSACTION_WRONG_SIZE_MESSAGE "Trunk transaction size must be 81 trytes"
#define BRANCH_TRANSACTION_WRONG_SIZE_MESSAGE "Branch transaction size must be 81 trytes"
#define TAG_WRONG_SIZE_MESSAGE "Tag size must be 27 trytes"
#define ADDRESS_MISSING_MESSAGE "Address is missing"
#define ADDRESS_NOT_STRING_MESSAGE "Address not string"
#define ADDRESS_WRONG_SIZE_MESSAGE "Address must be 81 trytes"

#endif //CRYPTO_CORE_ERROR_UTIL_H
