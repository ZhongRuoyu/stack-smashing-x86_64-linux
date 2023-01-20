// A tool which dumps the binary input file into a C unsigned char array.

#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input> <array-name>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) {
    fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
    return 1;
  }

  printf("static unsigned char %s[] = {", argv[2]);
  int chars_written = 0;
  for (int ch; (ch = fgetc(f)) != EOF;) {
    if (chars_written++ % 8 == 0) {
      printf("\n    ");
    } else {
      printf(" ");
    }
    printf("0x%02x,", (unsigned char)ch);
  }
  printf("\n};\n");

  fclose(f);
}
