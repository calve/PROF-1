#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string {
  char *ptr;
  size_t len;
};

void initStructString(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    printf("ERREUR: malloc!\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writeFonction(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    printf("ERREUR: realloc!\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}