#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  int size;
  int capacity;
  int *array;
} vector;

vector *create_vec() {
  int capacity = 1;

  vector *vector = malloc(sizeof(*vector) + sizeof(int) * capacity);

  vector->size = 0;
  vector->capacity = capacity;
  vector->array = (int *)malloc(sizeof(int) * capacity);

  return vector;
}

void free_vec(vector *vector) {
  free(vector->array);
  free(vector);
}

// TODO handle multi char numbers
char *string_from_vec(vector *vector) {
  int number_of_chars_per_element = 3;

  int number_of_chars = vector->size * number_of_chars_per_element;
  char *string = malloc(sizeof(char) * number_of_chars);

  for (size_t i = 0; i + 1 < number_of_chars;
       i += number_of_chars_per_element) {
    string[i] = vector->array[i / number_of_chars_per_element] + '0';

    if (i + number_of_chars_per_element <= number_of_chars - 1) {
      string[i + 1] = ',';
      string[i + 2] = ' ';
    }
  }

  string[number_of_chars - 1] = '\0';

  return string;
}

void append_vec(vector *vector, int value) {
  vector->size = vector->size + 1;

  if (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->array =
        (int *)realloc(vector->array, sizeof(int) * vector->capacity);
  }

  vector->array[vector->size - 1] = value;
}

void append_array_vec(vector *vector, int values[], size_t values_size) {

  int original_size = vector->size;

  vector->size = original_size + values_size;

  while (vector->size > vector->capacity) {
    vector->capacity *= 2;
    vector->array =
        (int *)realloc(vector->array, sizeof(int) * vector->capacity);
  }

  for (size_t i = 0; i < values_size; i++) {

    vector->array[original_size + i] = values[i];
  }
}

int main(void) {
  vector *vector = create_vec();

  append_vec(vector, 8);

  int values[] = {4, 3, 2, 1};
  append_array_vec(vector, values, sizeof(values) / sizeof(values[0]));
  append_vec(vector, 1);

  char *string = string_from_vec(vector);
  printf("Vector: %s\n", string);

  free_vec(vector);
  free(string);
  return 0;
}
