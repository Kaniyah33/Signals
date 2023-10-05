/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

clock_t start, end;
double timedif;
int alarm_count; //alarm counter variable

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  alarm(1);
  alarm_count ++; //adds to count to keep track of #of alarms
  printf("alarm in handler: ");
  //exit(1); //exit after printing
}

void handler2(int signum)
{ //signal handler

  end = clock();
  timedif = ((double)(end - start)/ CLOCKS_PER_SEC);
  printf("\nThe elapsed time is %f seconds\n", timedif);
  printf("\n%i alarms occurred\n", alarm_count);
  printf("\nExiting of the program...\n");
  exit(1);
}

int main(int argc, char * argv[])
{
  start = clock();
  signal(SIGALRM,handler); //register handler to handle SIGALRM 
  signal(SIGINT, handler2);
  alarm(1); //Schedule a SIGALRM for 1 second
  alarm_count ++; //adds to count to keep track of #of alarms
  printf("alarm in main: ");
  while(1){
    sleep(1);
    printf("Turing was right!\n");
  } //busy wait for signal to be delivered
  //signal(SIGINT, handler2); 
  return 0; //never reached
}
