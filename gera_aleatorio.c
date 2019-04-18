#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void random_gen() {
  printf("gerando\n");
  int random_nmbr = rand();
  FILE * fp = fopen("/tmp/numeros","w"); // breaks here
  fprintf(fp, "%d\n", random_nmbr);
  fclose(fp);
  printf("terminou a geracao\n");
}

void verify() {
  printf("verificando\n");
  FILE * f = fopen("/tmp/numeros","r");
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

void do_the_father_thing(pid_t son) {
  printf("father is ok. pid is %d\n", getpid());
  while (1) {
    sleep(1);
    kill(son, SIGUSR1); // the best comms function
    sleep(1);
    verify();
  }
}

void do_the_son_thing() {
  printf("son is up. pid: %d\n", getpid());
  signal(SIGUSR1, random_gen);
  while (1) sleep(1);
}

int main(int argc, char const *argv[]) {
  pid_t son = fork();
  printf("%d\n", getpid());

  if (son > 0) {  // I am your father
    do_the_father_thing(son);
  }
  else {
    do_the_son_thing();
  }

  return 0;
}
