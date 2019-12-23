#ifndef CRYPTO_CORE_ERROR_UTIL_H
#define CRYPTO_CORE_ERROR_UTIL_H

typedef enum {
    ERROR_MIN_WEIGHT_MAGNITUDE_MISSING,
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
    ERROR_BRANCH_TRANSACTION_MISSING,
    ERROR_BRANCH_TRANSACTION_NOT_STRING,
    ERROR_MIN_WEIGHT_MAGNITUDE_NOT_NUMBER,
    ERROR_TIMESTAMP_MISSING,
    ERROR_TIMESTAMP_NOT_NUMBER
} crypto_core_json_validation_error_t;

//set flags
#define SET_FLAGS_SUCCESSFUL_MESSAGE "Configuration of flags was successful."
#define SET_FLAGS_JSON_STRUCTURE_INVALID "The given json structure for the setFlags command is invalid."

#define FLAGS_MISSING_MESSAGE "The flags property is missing."
#define FLAGS_IS_NOT_OBJECT_MESSAGE "The flags property is not an object."
#define KEEP_SEED_IN_RAM_MISSING_MESSAGE "The keepSeedInRAM property is missing."
#define KEEP_SEED_IN_RAM_EMPTY_MESSAGE "keepSeedInRAM property is empty."
#define KEEP_SEED_IN_RAM_NOT_BOOL_MESSAGE "keepSeedInRAM property is not a bool."

//do pow
#define MIN_WEIGHT_MAGNITUDE_MISSING_MESSAGE "The property minWeightMagnitude is missing."
#define MIN_WEIGHT_MAGNITUDE_NOT_INTEGER_MESSAGE "The property minWeightMagnitude is not an integer."
#define TRYYES_NOT_ARRAY_MESSAGE "The property trytes is not an array."
#define TRYTES_ARRAY_NOT_STRING_MESSAGE "The property trytes must contain only strings."

//attach to tangle
#define TRUNK_TRANSACTION_MISSING_MESSAGE "trunkTransaction property is missing."
#define TRUNK_TRANSACTION_NOT_STRING_MESSAGE "trunkTransaction is not a string."
#define BRANCH_TRANSACTION_MISSING_MESSAGE "branchTransaction property is missing."
#define BRANCH_TRANSACTION_NOT_STRING_MESSAGE "branchTransaction is not a string."
#define MIN_WEIGHT_MAGNITUDE_NOT_NUMBER_MESAGE "minWeightMagnitude is not a number."
#define TIMESTAMP_MISSING_MESSAGE "timestamp property is missing."
#define TIMESTAMP_NOT_NUMBER_MESSAGE "timestamp is not an integer."
#define TRYTES_MISSING_MESSAGE "trytes property is missing."
#define TRYTES_NOT_ARRAY_MESSAGE "trytes is not an array."

#endif //CRYPTO_CORE_ERROR_UTIL_H
