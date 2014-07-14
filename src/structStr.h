#ifndef STRUCTSTR
#define STRUCTSTR

struct string {
  char *ptr;
  size_t len;
};

void initStructString(struct string*);
size_t writeFonction(void*, size_t, size_t, struct string*);

#endif