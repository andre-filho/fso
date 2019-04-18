#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void random_gen() {
  printf("gerando\n");
  int random_nmbr = rand();
  FILE * fp = fopen("/tmp/numeros", "w");
  fprintf(fp, "%d\n", random_nmbr);
  fclose(fp);
  printf("terminou a geracao\n");
}

void verify() {
  printf("verificando\n");
  FILE * f = fopen("/tmp/numeros", "r");
  int n;
  fscanf(f, "%d\n", &n);
  if (n % 2 <= 0) {
    printf("%d is even\n", n);
  }
  else {
    printf("%d is odd\n", n);
  }
  fclose(f);
  printf("terminou a verificacao\n");
}

void do_the_son_thing() {
  printf("son is ok. pid is %d\n", getpid());
  while (1) {
    kill(getppid(), SIGUSR1); // the best comms function
    sleep(1);
    verify();
  }
}

void do_the_father_thing() {
  printf("father is up. pid: %d\n", getpid());
  signal(SIGUSR1, random_gen);
}

void father() {
  int * wtf;
  
}

int main(int argc, char const *argv[]) {
  pid_t son = fork();

  if (son > 0) {  // I am your father
    do_the_father_thing();
  }
  else {
    do_the_son_thing();
  }

  return 0;
}
