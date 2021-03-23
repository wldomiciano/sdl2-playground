#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef struct List List;
typedef struct Node Node;

List* list_create(void (*destructor)(void* value));
void list_destroy(List* list);
void list_add(List* list, void* value);
uint32_t list_length(List* list);
void list_foreach(List* list, void (*fn)(void* value));
void* list_remove_by_index(List* list, uint32_t index);
void list_remove_by_pointer(List* list, void* value);

#endif  // !LIST_H