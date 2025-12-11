#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int contador = 0;

void* inc(void* arg) 
{
  for(int i = 0; i < 1000000; i++) 
  {
    contador++;
  }
  return NULL;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, inc, NULL);
  pthread_create(&t2, NULL, inc, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("%d\n", contador);
  return 0;
}

