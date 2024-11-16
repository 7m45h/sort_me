#pragma once

void flogg_error(const char* file_name, int line, const char* function_name, int error_number, const char* error_msg);
void flogg_failure(const char* file_name, int line, const char* function_name);
