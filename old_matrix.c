#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int m1[1000][1000], m2[1000][1000], m3[1000][1000];

void printa_ae(int size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
        printf("%d ", m3[i][j]);
    }
    printf("\n");
  }
}

void pos(int a, int b, int size) {
  m3[a][b] = 0;
  for (size_t i = 0; i < size; i++) {
    m3[a][b] += m1[a][i] * m2[i][b];
  }
}

int main(int argc, char const *argv[]) {
  int size = 0;
  scanf("%d\n", &size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      scanf("%d\n", &m1[i][j]);
    }
  }
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      scanf("%d\n", &m2[i][j]);
    }
  }
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      pos(i, j, size);
    }
  }
  return 0;
}
