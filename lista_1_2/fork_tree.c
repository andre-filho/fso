// 150005521 andre de sousa costa filho

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void wait_for_it ()
{
  int status;

  wait(&status);
}

void print_graph ()
{
  printf("%d -- %d;\n", getppid (), getpid ());
}

void do_the_last_sons_stuff ()
{
  print_graph ();
}

void make_single_son ()
{
  wait_for_it ();
  if (fork () == 0)
  {
    wait_for_it ();
    do_the_last_sons_stuff ();
    wait_for_it ();
    printf("}\n");
  }
}

void create_child_process ()
{
  do_the_last_sons_stuff ();

  wait_for_it ();
  
  if (fork () == 0)
  {
    wait_for_it ();
    do_the_last_sons_stuff ();
  }
  
  else if (fork () == 0)
  {
    wait_for_it ();
    
    do_the_last_sons_stuff ();
    wait_for_it ();
  }
  
  else if (fork () == 0)
  {
    wait_for_it ();
    do_the_last_sons_stuff ();
    
    wait_for_it ();
    make_single_son ();
    
    wait_for_it ();
  }
}

int main ()
{

  printf("graph {\n");
  print_graph ();

  wait_for_it ();

  if (fork () == 0)
  {
    wait_for_it ();
  
    do_the_last_sons_stuff ();
  
    wait_for_it ();
  }
  
  else if (fork () == 0)
  {
    wait_for_it ();
  
    do_the_last_sons_stuff ();
  
    wait_for_it ();
  }
  
  else if (fork () == 0)
  {
    wait_for_it ();
  
    create_child_process ();
  
    wait_for_it ();
  }
  
  else if (fork () == 0)
  {
    wait_for_it ();
  
    do_the_last_sons_stuff ();
  
    wait_for_it ();
  }

  return 0;
}
