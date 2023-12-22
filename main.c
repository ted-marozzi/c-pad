#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
  unsigned long long length;
  unsigned long long capacity;
  char *chars;
} String;

String *string_create() {
  int capacity = 2;

  String *string = malloc(sizeof(*string) + sizeof(char) * capacity);

  string->length = 0;
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
  int original_size = string->length;

  string->length = original_size + chars_size;

  while (string->length > string->capacity) {
    string->capacity *= 2;
    string->chars =
        (char *)realloc(string->chars, sizeof(char) * string->capacity);
  }

  for (size_t i = 0; i < chars_size; i++) {
    string->chars[original_size + i] = chars[i];
  }
}

void string_append_string(String *string, String *string_two) {
  string_append_chars(string, string_two->chars);
}

char *string_to_chars(String *string) {
  char *chars = (char *)malloc(sizeof(char) * string->length + 1);

  for (size_t i = 0; i < string->length; i++) {
    chars[i] = string->chars[i];
  }

  chars[string->length] = '\0';

  return chars;
}

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

int main(void) {
  Vector *vector = vec_create();
  vec_append(vector, 1);

  printf("Item: %d\n", vec_get_item(vector, 0));
  vec_set_item(vector, 0, 100);
  printf("Item: %d\n", vec_get_item(vector, 0));

  Vector *vector_two = vec_create();
  vec_append(vector_two, 2);
  vec_append(vector_two, 3);

  vec_append_vec(vector, vector_two);

  int array[] = {INT_MIN, 0, INT_MAX};
  vec_append_array(vector, array, sizeof(array) / sizeof(array[0]));

  printf("Vector: %s\n", vec_to_chars(vector));

  String *string = string_create();
  string_append_chars(string, "Hello, ");
  string_append_chars(string, "World!\n");
  string_append_string(string, vec_to_string(vector));

  printf("String: %s\n", string_to_chars(string));

  vec_free(vector);
  vec_free(vector_two);
  string_free(string);

  return 0;
}
