#pragma once

#include <stdio.h>

struct int_array
{
    size_t capacity;
    size_t   length;
    int*       data;
};

struct int_array* int_array_create(int capacity);
void              int_array_destroy(struct int_array* iarr);

void int_array_fill(struct int_array* iarr);
void int_array_suffle(struct int_array* iarr);
