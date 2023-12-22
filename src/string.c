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

  string->length = original_size + chars_size + 1;

  while (string->length > string->capacity) {
    string->capacity *= 2;
    if (string->capacity > ULLONG_MAX / 2) {
      printf("String capacity overflow\n");
      exit(1);
    }
  }
  string->chars =
      (char *)realloc(string->chars, sizeof(char) * string->capacity);

  for (size_t i = 0; i < chars_size; i++) {
    string->chars[original_size + i] = chars[i];
  }

  // TODO: Invalid write of size 1
  string->chars[string->length] = '\0';
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
