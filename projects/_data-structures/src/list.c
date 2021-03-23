#include "list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  void* value;
  Node* next;
};

struct List {
  void (*destructor)(void* value);
  uint32_t length;
  Node* first;
  Node* last;
};

static Node* node_create() {
  return calloc(1, sizeof(Node));
}

static void node_destroy(List* list, Node* node) {
  if (node) {
    node_destroy(list, node->next);

    if (list->destructor && node->value) {
      list->destructor(node->value);
    }

    free(node);
  }
}

List* list_create(void (*destructor)(void* value)) {
  List* list = calloc(1, sizeof(List));

  if (list && destructor) {
    list->destructor = destructor;
  }

  return list;
}

void list_destroy(List* list) {
  if (list) {
    node_destroy(list, list->first);
    free(list);
  }
}

void list_add(List* list, void* value) {
  if (list && value) {
    Node* node = node_create();

    if (node) {
      node->value = value;

      if (list->length > 0) {
        list->last->next = node;
        list->last = node;
      } else {
        list->first = list->last = node;
      }

      list->length++;
    }
  }
}

void* list_remove_by_index(List* list, uint32_t index) {
  void* value = NULL;
  Node* node = NULL;

  if (list && index < list->length) {
    if (index == 0 && list->first) {
      node = list->first;
      list->first = node->next;
    } else {
      uint32_t i = 1;
      for (Node* n = list->first; n; n = n->next) {
        if (i++ == index && n->next) {
          node = n->next;
          n->next = node->next;
          break;
        }
      }
    }
  }

  if (node) {
    value = node->value;
    list->length--;
    free(node);
  }

  return value;
}

void list_remove_by_pointer(List* list, void* value) {
  Node* node = NULL;

  if (list && list->first) {
    if (list->first->value == value) {
      node = list->first;
      list->first = node->next;
    } else {
      for (Node* n = list->first; n; n = n->next) {
        if (n->next && n->next->value == value) {
          node = n->next;
          n->next = node->next;
          break;
        }
      }
    }
  }

  if (node) {
    free(node);
    list->length--;
  }
}

uint32_t list_length(List* list) {
  return list->length;
}

void list_foreach(List* list, void (*fn)(void* value)) {
  if (list) {
    for (Node* n = list->first; n; n = n->next) {
      fn(n->value);
    }
  }
}