#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t ping_sem;
sem_t pong_sem;

void* thread_ping(void* arg) 
{
  int i = 0;
  while(i <= 10) 
  {
    sem_wait(&ping_sem);
    printf("PING\n");
    fflush(stdout);
    sem_post(&pong_sem);
    i++;
  }
  return NULL;
}

void* thread_pong(void* arg) 
{
  int i = 0;
  while(i <= 10)
  {
    sem_wait(&pong_sem);
    printf("PONG\n");
    fflush(stdout);
    sem_post(&ping_sem);
    i++;
  }
  return NULL;
}

int main() 
{
  sem_init(&ping_sem, 0, 1);
  sem_init(&pong_sem, 0, 0);
  pthread_t a, b;
  pthread_create(&a, NULL, thread_ping, NULL);
  pthread_create(&b, NULL, thread_pong, NULL);
  pthread_join(a, NULL);
  pthread_join(b, NULL);
  return 0;
}
