#include "peachdb.h"

void init_storage(char *filename, User *users, int size) {
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    fprintf(stderr, "Error: cannot open file\n");
    exit(1);
  }

  fwrite(users, sizeof(User), size, fp);
  fclose(fp);
}

unsigned long get_size(char *filename) {
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    fprintf(stderr, "Error: cannot open file\n");
    exit(1);
  }

  fseek(fp, 0, SEEK_END);
  unsigned long size = ftell(fp) / sizeof(User);

  fclose(fp);
  return size;
}

void load_storage(char *filename, User *users, unsigned long size) {
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    fprintf(stderr, "Error: cannot open file\n");
    exit(1);
  }

  fread(users, sizeof(User), size, fp);
  fclose(fp);
}
