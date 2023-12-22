#ifndef VECTOR_H
#define VECTOR_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct String String;

typedef struct Vector {
  unsigned long long length;
  unsigned long long capacity;
  int *items;
} Vector;

Vector *vec_create();
void vec_free(Vector *vector);
int vec_get_item(Vector *vector, int index);
void vec_set_item(Vector *vector, int index, int item);
String *vec_to_string(Vector *vector);
char *vec_to_chars(Vector *vector);
void vec_append(Vector *vector, int item);
void vec_append_array(Vector *vector, int items[], size_t items_size);
void vec_append_vec(Vector *vector, Vector *vector_to_append);
Vector *vec_clone(Vector *vector);

#endif
