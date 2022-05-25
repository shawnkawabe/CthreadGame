#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

void *myfunc(void *arg)
{
  printf("Running thread...");

  char *outra_string = (char *)arg;
  printf("%s\n", outra_string);
  
  sprintf(outra_string, "%s", "BATMAN");

}

int main(void) {
  pthread_t thread_id;

  char string[10] = "BANANA";
  
  pthread_create(&thread_id, NULL, myfunc, (void *)string);
  pthread_join(thread_id, NULL);

  printf("\nAfter thread\n");
  printf("%s", string);
}