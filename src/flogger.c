#include <stdio.h>

#include "flogger.h"

void flogg_error(const char* file_name, int line, const char* function_name, int error_number, const char* error_msg)
{
    fprintf(stderr, "[ %24s:%04d ] -> ", file_name, line);
    fprintf(stderr, "%24s --+-> |%04d| : %s", function_name, error_number, error_msg);
    fputc('\n', stderr);
}

void flogg_failure(const char* file_name, int line, const char* function_name)
{
    fprintf(stderr, "[ %24s:%04d ] -> ", file_name, line);
    fprintf(stderr,"%24s <-|", function_name);
    fputc('\n', stderr);
}
