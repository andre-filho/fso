#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void report() {
  printf("me:%d my dad:%d\n", getpid(), getppid());
}

void faz_o_que_o_b_faz() {
  report();
  if (fork() == 0) {
    report();
  }
}

void faz_o_que_o_c_faz() {
  report();
  if (fork() == 0) {
    faz_o_que_o_b_faz();
  }
  else {
    if (fork() == 0) {
      faz_o_que_o_b_faz();
    }
  }
}

int main(int argc, char const *argv[]) {
  printf("root: %d\n", getpid());

  if (fork()) {
    pid_t retf;
    retf = fork();

    if (retf == 0) {
      faz_o_que_o_b_faz();
    }
    else {
      if (fork == 0) {
        faz_o_que_o_c_faz();
      }
    }
  }

  return 0;
}
