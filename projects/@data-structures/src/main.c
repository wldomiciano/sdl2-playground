#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "list.h"

typedef struct {
  char name[30];
  int age;
} Person;

static void print_person(void* value) {
  Person* p = value;
  printf("{ name: %s, age: %d }\n", p->name, p->age);
}

static Person* person_create(const char* name, int age) {
  Person* p = malloc(sizeof(*p));

  if (p) {
    strncpy(p->name, name, sizeof(p->name));
    p->age = age;
  }

  return p;
}

static void print_name(void* n) {
  printf(">> %s\n", ( char* ) n);
}

static void print_age(void* n) {
  printf(">> %d\n", *(( int* ) n));
}

static void* map_names(void* p) {
  Person* person = p;
  return person->name;
}

static void* map_ages(void* p) {
  Person* person = p;
  return &person->age;
}

static bool filter_greater18(void* p) {
  Person* person = p;
  return (person->age > 18);
}

static void person_destructor(void* p) {
  free(p);
}

int main() {
  List* list = list_create(person_destructor);
  Person* p1 = person_create("xxx", 18);

  list_add(list, person_create("João", 18));
  list_add(list, person_create("Ana", 32));
  list_add(list, person_create("Marcelo", 49));
  list_add(list, p1);
  list_add(list, person_create("Marta", 31));
  list_add(list, person_create("Agenor", 28));

  list_remove_by_pointer(list, p1);
  free(p1);

  list_foreach(list, print_person);

  list_destroy(list);

  //
  //
  //

  Array* arr = array_create(3, sizeof(Person));

  array_push(arr, &(Person){"Pedro", 18});
  array_push(arr, &(Person){"Maria", 23});
  array_push(arr, &(Person){"Dario", 36});

  Array* names = array_map(arr, 30, map_names);
  Array* ages = array_map(arr, sizeof(int), map_ages);
  Array* greater18s = array_filter(arr, filter_greater18);

  array_foreach(arr, print_person);
  array_foreach(names, print_name);
  array_foreach(ages, print_age);
  array_foreach(greater18s, print_person);

  array_destroy(greater18s);
  array_destroy(ages);
  array_destroy(names);
  array_destroy(arr);

  return 0;
}