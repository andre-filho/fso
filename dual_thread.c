#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int m1[1000][1000], m2[1000][1000], m3[1000][1000];
int size = 0;
int thread_qtd = 2;

pthread_t id1, id2;

void printa_ae() {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
        printf("%d ", m3[i][j]);
    }
    printf("\n");
  }
}

void pos(int a, int b) {
  m3[a][b] = 0;
  for (size_t i = 0; i < size; i++) {
    m3[a][b] += m1[a][i] * m2[i][b];
  }
}

void multiplica_ae(int a) {
  for (size_t i = a; i < (size/thread_qtd) + a; i++) {
    for (size_t j = 0; j < size; j++) {
      pos(i, j);
    }
  }
}

void * thread_1(void * cu) {
  multiplica_ae(0);
  pthread_exit(NULL);
}

void * thread_2(void * cu) {
  multiplica_ae(size/thread_qtd);
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
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

  pthread_create(&id1, NULL, (void*) thread_1, NULL);
  pthread_create(&id2, NULL, (void*) thread_2, NULL);

  sleep(1);
  printa_ae();

  return 0;
}
