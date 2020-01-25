#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/37496282/c-generic-array-implementation

typedef struct Array Array;

Array* array_create(uint32_t capacity, size_t elementSize);
void array_destroy(Array* arr);
uint32_t array_shrink(Array* arr);

int32_t array_push(Array* arr, void* item);
void* array_get(const Array* arr, uint32_t index);

uint32_t array_length(const Array* arr);
uint32_t array_element_size(const Array* arr);
uint32_t array_capacity(const Array* arr);

Array* array_filter(const Array* arr, bool (*fn)(void*));
Array* array_map(const Array* arr, size_t size, void* (*fn)( void* ) );
void array_foreach(const Array* arr, void (*fn)(void*));

#endif  // !ARRAY_H