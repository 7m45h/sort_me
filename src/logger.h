#pragma once

#include <stdio.h>

#include "flogger.h"

#define LOGG_UNKNOWN_CODE 9999
#define LOGG_UNKNOWN_MSG  "unknown error message"

#define LOGG(...) \
    fprintf(stderr, "[ %24s:%04d ] -> ", __FILE_NAME__, __LINE__); \
    fprintf(stderr, __VA_ARGS__); \
    putc('\n', stderr)

#define LOGG_ERROR(function_name, error_number, error_msg) flogg_error(__FILE_NAME__, __LINE__, function_name, error_number, error_msg)

#define LOGG_FAILURE(function_name) flogg_failure(__FILE_NAME__, __LINE__, function_name)
