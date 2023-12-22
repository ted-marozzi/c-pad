#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
  int size;
  int capacity;
  char *chars;
} String;

String *string_create() {
  int capacity = 1;

  String *string = malloc(sizeof(*string) + sizeof(char) * capacity);

  string->size = 0;
  string->capacity = capacity;
  string->chars = (char *)malloc(sizeof(char) * capacity);

  return string;
}

void string_free(String *string) {
  free(string->chars);
  free(string);
}

void string_append_chars(String *string, char *chars) {
  int chars_size = strlen(chars);
  int original_size = string->size;

  string->size = original_size + chars_size;

  while (string->size > string->capacity) {
    string->capacity *= 2;
    string->chars =
        (char *)realloc(string->chars, sizeof(char) * string->capacity);
  }

  for (size_t i = 0; i < chars_size; i++) {
    string->chars[original_size + i] = chars[i];
  }
}

char *string_to_chars(String *string) {
  char *chars = (char *)malloc(sizeof(char) * string->size + 1);

  for (size_t i = 0; i < string->size; i++) {
    chars[i] = string->chars[i];
  }

  chars[string->size] = '\0';

  return chars;
}

typedef struct Vector {
  int size;
  int capacity;
  int *items;
} Vector;

Vector *vec_create() {
  int capacity = 1;

  Vector *vector = malloc(sizeof(*vector) + sizeof(int) * capacity);

  vector->size = 0;
  vector->capacity = capacity;
  vector->items = (int *)malloc(sizeof(int) * capacity);

  return vector;
}

void vec_free(Vector *vector) {
  free(vector->items);
  free(vector);
}

int vec_get_item(Vector *vector, int index) {
  if (index >= vector->size) {
    printf("Index out of bounds\n");
    exit(1);
  }
  return vector->items[index];
}

void vec_set_item(Vector *vector, int index, int item) {
  if (index >= vector->size) {
    printf("Index out of bounds\n");
    exit(1);
  }
  vector->items[index] = item;
}

String *vec_to_string(Vector *vector) {
  String *string = string_create();

  for (size_t i = 0; i < vector->size; i++) {
    int formatting_count = 4;
    int digit_count = 11;
    int null_terminator_count = 1;

    int max_chars_count =
        formatting_count + digit_count + null_terminator_count;

    char buffer[max_chars_count];
    if (i == 0) {
      char *str1 = "quick";
      char *str2 = "brown";
      char *str3 = "lazy";
      snprintf(buffer, sizeof buffer, "{ %d, ", vec_get_item(vector, i));
    } else if (i < vector->size - 1) {
      snprintf(buffer, sizeof buffer, "%d, ", vec_get_item(vector, i));
    } else {
      snprintf(buffer, sizeof buffer, "%d }", vec_get_item(vector, i));
    }
    string_append_chars(string, buffer);
  }

  return string;
}

void vec_append(Vector *vector, int item) {
  vector->size = vector->size + 1;

  if (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->items =
        (int *)realloc(vector->items, sizeof(int) * vector->capacity);
  }

  vector->items[vector->size - 1] = item;
}

void vec_append_array(Vector *vector, int items[], size_t items_size) {

  int original_size = vector->size;

  vector->size = original_size + items_size;

  while (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->items =
        (int *)realloc(vector->items, sizeof(int) * vector->capacity);
  }

  for (size_t i = 0; i < items_size; i++) {
    vec_set_item(vector, original_size + i, items[i]);
  }
}

int main(void) {
  Vector *vector = vec_create();

  int items[] = {INT_MIN, INT_MAX, 2};
  vec_append_array(vector, items, sizeof(items) / sizeof(int));
  vec_append(vector, 1);

  String *vector_string = vec_to_string(vector);
  char *vector_chars = string_to_chars(vector_string);
  printf("Vector: %s\n", vector_chars);

  vec_free(vector);
  string_free(vector_string);
  free(vector_chars);

  return 0;
}
