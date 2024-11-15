#pragma once

#include <stdio.h>

#define LOGG_UNKNOWN_CODE 9999
#define LOGG_UNKNOWN_MSG  "unknown error message"

#define LOGG(...) \
  fprintf(stderr, "[ %24s:%04d ] -> ", __FILE_NAME__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
  putc('\n', stderr)

#define LOGG_ERROR(function_name, error_number, error_string) LOGG("%24s --+-> |%04d| : %s", function_name, error_number, error_string)

#define LOGG_FAILURE(function_name) LOGG("%24s <-|", function_name)
