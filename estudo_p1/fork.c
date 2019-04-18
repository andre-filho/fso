#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void C()
{
  pid_t me = fork();
  if (me == 0)
  {
    printf("I am C. PID= %d PPID= %d\n\n", getpid(), getppid());
    pid_t son_of_c = fork();
    if (son_of_c == 0)
    {
      printf("I am Echo, son of C. PID= %d PPID= %d\n\n", getpid(), getppid());
      exit(0);
    }
    sleep(1);
    exit(0);
  }
}

void D()
{
  pid_t d, f, g;
  d = fork();
  if (d == 0)
  {
    printf("I am D, the destroyer. PID= %d PPID= %d\n\n", getpid(), getppid());
    f = fork();
    if (f == 0)
    {
      printf("I am Fox, the blue fox. PID= %d PPID= %d\n\n", getpid(), getppid());
      exit(0);
    }
    g = fork();
    if (g == 0)
    {
      printf("I am G, also known as Gatsby. PID= %d PPID= %d\n\n", getpid(), getppid());
      exit(0);
    }
    sleep(1);
  }
}

int main(int argc, char const *argv[])
{
  printf("I am Odin, the All-father! PID= %d\n\n", getpid());

  pid_t b = fork();

  if (b == 0)
  {
    printf("I am B. PID= %d, PPID= %d\n\n", getpid(), getppid());
    exit(0);
  }
  else
  {
    C();
    D();
  }

  wait(NULL);
  return 0;
}
