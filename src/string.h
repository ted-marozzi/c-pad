#ifndef STRING_H
#define STRING_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
  unsigned long long length;
  unsigned long long capacity;
  char *chars;
} String;

String *string_create();
void string_free(String *string);
void string_append_chars(String *string, char *chars);
void string_append_string(String *string, String *string_two);
char *string_to_chars(String *string);

#endif
