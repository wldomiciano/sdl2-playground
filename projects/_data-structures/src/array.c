#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

struct Array {
  uint8_t* elements;
  size_t elementSize;
  uint32_t length;
  uint32_t capacity;
};

Array* array_create(uint32_t capacity, size_t elementSize) {
  if (capacity > 0 && elementSize > 0) {
    Array* arr = malloc(sizeof(*arr));

    if (arr != NULL) {
      arr->length = 0;
      arr->capacity = capacity;
      arr->elementSize = elementSize;
      arr->elements = calloc(capacity, arr->elementSize);

      if (arr->elements == NULL) {
        free(arr);
        arr = NULL;
      }
    }

    return arr;
  }

  return NULL;
}

uint32_t array_shrink(Array* arr) {
  if (arr) {
    uint32_t length = array_length(arr);
    uint32_t capacity = array_capacity(arr);

    if (length > 0 && length < capacity) {
      void* data = realloc(arr->elements, length * arr->elementSize);

      if (data) {
        arr->capacity = length;
        arr->elements = data;
        return length;
      }
    }

    return capacity;
  }

  return -1;
}

int32_t array_push(Array* arr, void* item) {
  if (arr && arr->length < arr->capacity) {
    memcpy(arr->elements + arr->length * arr->elementSize, item,
           arr->elementSize);
    return arr->length++;
  }

  return -1;
}

void* array_get(const Array* arr, uint32_t index) {
  if (arr && index < arr->length) {
    return arr->elements + index * arr->elementSize;
  }

  return NULL;
}

uint32_t array_length(const Array* arr) {
  return arr ? arr->length : 0;
}

uint32_t array_element_size(const Array* arr) {
  return arr ? arr->elementSize : 0;
}

uint32_t array_capacity(const Array* arr) {
  return arr ? arr->capacity : 0;
}

void array_destroy(Array* arr) {
  if (arr) {
    if (arr->elements) {
      free(arr->elements);
    }

    free(arr);
  }
}

void array_foreach(const Array* arr, void (*fn)(void*)) {
  for (int i = 0, length = array_length(arr); i < length; i++) {
    fn(array_get(arr, i));
  }
}

Array* array_filter(const Array* arr, bool (*fn)(void*)) {
  if (arr) {
    const uint32_t length = array_length(arr);
    Array* filtered = array_create(length, array_element_size(arr));

    if (filtered) {
      for (uint32_t i = 0; i < length; i++) {
        void* element = array_get(arr, i);

        if (fn(element)) {
          array_push(filtered, element);
        }
      }

      array_shrink(filtered);
    }

    return filtered;
  }

  return NULL;
}

Array* array_map(const Array* arr, size_t size, void* (*fn)( void* ) ) {
  if (arr) {
    const uint32_t length = array_length(arr);
    Array* mapped = array_create(length, size);

    if (mapped) {
      for (uint32_t i = 0; i < length; i++) {
        array_push(mapped, fn(array_get(arr, i)));
      }
    }

    return mapped;
  }

  return NULL;
}
