#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
  int size;
  int capacity;
  int *array;
} vector;

vector *vec_create() {
  int capacity = 1;

  vector *vector = malloc(sizeof(*vector) + sizeof(int) * capacity);

  vector->size = 0;
  vector->capacity = capacity;
  vector->array = (int *)malloc(sizeof(int) * capacity);

  return vector;
}

void vec_free(vector *vector) {
  free(vector->array);
  free(vector);
}

int vec_get_item(vector *vector, int index) {
  if (index >= vector->size) {
    printf("Index out of bounds\n");
    exit(1);
  }
  return vector->array[index];
}

void vec_set_item(vector *vector, int index, int item) {
  if (index >= vector->size) {
    printf("Index out of bounds\n");
    exit(1);
  }
  vector->array[index] = item;
}

// TODO create a dynamic string class and use here instead of huge buffer
char *vec_to_string(vector *vector) {
  int buffer_size = 10000;
  char *string = (char *)malloc(sizeof(char) * buffer_size);

  for (size_t i = 0; i < vector->size; i++) {
    int formatting_count = 4;
    int digit_count = 11;
    int null_terminator_count = 1;

    int max_number_chars =
        formatting_count + digit_count + null_terminator_count;

    char number[max_number_chars];
    if (i == 0) {
      sprintf(number, "{ %d, ", vec_get_item(vector, i));
    } else if (i < vector->size - 1) {
      sprintf(number, "%d, ", vec_get_item(vector, i));
    } else {
      sprintf(number, "%d }", vec_get_item(vector, i));
    }
    strcat(string, number);
  }

  return string;
}

void vec_append(vector *vector, int item) {
  vector->size = vector->size + 1;

  if (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->array =
        (int *)realloc(vector->array, sizeof(int) * vector->capacity);
  }

  vector->array[vector->size - 1] = item;
}

void vec_append_array(vector *vector, int items[], size_t items_size) {

  int original_size = vector->size;

  vector->size = original_size + items_size;

  while (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->array =
        (int *)realloc(vector->array, sizeof(int) * vector->capacity);
  }

  for (size_t i = 0; i < items_size; i++) {
    vec_set_item(vector, original_size + i, items[i]);
  }
}

void vec_append_vec(vector *vector, int items[], size_t items_size) {

  int original_size = vector->size;

  vector->size = original_size + items_size;

  while (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->array =
        (int *)realloc(vector->array, sizeof(int) * vector->capacity);
  }

  for (size_t i = 0; i < items_size; i++) {
    vec_set_item(vector, original_size + i, items[i]);
  }
}

int main(void) {
  vector *vector = vec_create();

  int items[] = {INT_MIN, INT_MAX, 2};
  vec_append_array(vector, items, sizeof(items) / sizeof(int));
  vec_append(vector, 1);

  char *string = vec_to_string(vector);
  printf("Vector: %s\n", string);

  vec_free(vector);
  free(string);
  return 0;
}
