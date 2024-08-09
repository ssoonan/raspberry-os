#include "stdio.h"
#include "string.h"

char str1[9] = "aabbccdd";
char str2[9] = "aabbccdd";

int main(void)
{
  printf("The string: %s\n", str1);
  memcpy(str1 + 2, str1, 6);
  printf("New string: %s\n", str1);

  // strcpy_s(str1, sizeof(str1), "aabbccdd"); // reset string

  printf("The string: %s\n", str2);
  memmove(str2 + 2, str2, 6);
  printf("New string: %s\n", str2);
}