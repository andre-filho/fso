#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

sem_t sem, sem2;
pthread_t tid1, tid2, tid3, tid4;

void *thread1(void *_) {
  sem_wait(&sem);             // double the wait makes the thread3 execute first
  sem_wait(&sem);
  printf("asdf 1\n");
}

void *thread2(void *_) {
  printf("asdf 2\n");
  sem_post(&sem2);
}

void *thread3(void *_) {
  printf("asdf 3\n");
  sem_post(&sem);
}

void *thread4(void *_) {
  sem_wait(&sem2);
  sem_wait(&sem2);
  printf("asdf 4\n");
}

int main(int argc, char const *argv[]) {
  sem_init(&sem, 0, 1);
  sem_init(&sem2, 0, 1);
  
  pthread_create(&tid1, NULL, (void *)thread1, NULL);
  pthread_create(&tid2, NULL, (void *)thread2, NULL);
  pthread_create(&tid3, NULL, (void *)thread3, NULL);
  pthread_create(&tid4, NULL, (void *)thread4, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);

  printf("finished\n");
  return 0;
}
