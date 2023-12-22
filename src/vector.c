#include "string.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  unsigned long long length;
  unsigned long long capacity;
  int *items;
} Vector;

Vector *vec_create() {
  int capacity = 2;

  Vector *vector = malloc(sizeof(*vector) + sizeof(int) * capacity);

  vector->length = 0;
  vector->capacity = capacity;
  vector->items = (int *)malloc(sizeof(int) * capacity);

  return vector;
}

void vec_free(Vector *vector) {
  free(vector->items);
  free(vector);
}

int vec_get_item(Vector *vector, int index) {
  if (index >= vector->length) {
    printf("Unable to get item, index out of bounds\n");
    exit(1);
  }
  return vector->items[index];
}

void vec_set_item(Vector *vector, int index, int item) {
  if (index >= vector->length) {
    printf("Unable to set item, index out of bounds\n");
    exit(1);
  }
  vector->items[index] = item;
}

String *vec_to_string(Vector *vector) {
  String *string = string_create();

  for (size_t i = 0; i < vector->length; i++) {
    int formatting_count = 4;
    int digit_count = 11;
    int null_terminator_count = 1;

    int max_chars_count =
        formatting_count + digit_count + null_terminator_count;

    char buffer[max_chars_count];
    if (i == 0) {
      if (vector->length == 1) {
        snprintf(buffer, sizeof buffer, "{ %d }", vec_get_item(vector, i));
      } else {
        snprintf(buffer, sizeof buffer, "{ %d, ", vec_get_item(vector, i));
      }
    } else if (i < vector->length - 1) {
      snprintf(buffer, sizeof buffer, "%d, ", vec_get_item(vector, i));
    } else {
      snprintf(buffer, sizeof buffer, "%d }", vec_get_item(vector, i));
    }
    string_append_chars(string, buffer);
  }

  return string;
}

char *vec_to_chars(Vector *vector) {
  String *string = vec_to_string(vector);
  char *chars = string_to_chars(string);
  string_free(string);
  return chars;
}

void vec_append(Vector *vector, int item) {
  vector->length = vector->length + 1;

  if (vector->length > vector->capacity) {
    vector->capacity *= 2;
    vector->items =
        (int *)realloc(vector->items, sizeof(int) * vector->capacity);
  }

  vector->items[vector->length - 1] = item;
}

void vec_append_array(Vector *vector, int items[], size_t items_size) {
  int original_size = vector->length;

  vector->length = original_size + items_size;

  while (vector->length > vector->capacity) {
    if (vector->capacity > ULLONG_MAX / 2) {
      printf("Vector capacity overflow\n");
      exit(1);
    }
    vector->capacity *= 2;
  }
  vector->items = (int *)realloc(vector->items, sizeof(int) * vector->capacity);

  for (size_t i = 0; i < items_size; i++) {
    int item = items[i];
    vec_set_item(vector, original_size + i, item);
  }
}

void vec_append_vec(Vector *vector, Vector *vector_to_append) {
  vec_append_array(vector, vector_to_append->items, vector_to_append->length);
}

Vector *vec_clone(Vector *vector) {
  Vector *new_vector = vec_create();

  vec_append_vec(new_vector, vector);

  return new_vector;
}
