#include "string.h"
#include "vector.h"
#include <limits.h>

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

  char *vec_chars = vec_to_chars(vector);
  printf("Vector: %s\n", vec_chars);

  String *string = string_create();
  string_append_chars(string, "Hello, ");
  string_append_chars(string, "World!\n");

  String *vec_string = vec_to_string(vector);
  string_append_string(string, vec_string);

  char *string_chars = string_to_chars(string);
  printf("Chars: %s\n", string_chars);

  vec_free(vector);
  vec_free(vector_two);
  string_free(string);
  string_free(vec_string);
  free(string_chars);
  free(vec_chars);

  return 0;
}
