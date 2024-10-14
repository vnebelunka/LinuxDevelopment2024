#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("help\n");
    return 0;
  }
  int N = argc > 2 ? atoi(argv[2]) : atoi(argv[1]);
  int M = argc > 2 ? atoi(argv[1]) : 0;
  int S = argc > 3 ? atoi(argv[3]) : 1;
  for (int i = M; i < N; i += S) {
    printf("%d\n", i);
  }
}
