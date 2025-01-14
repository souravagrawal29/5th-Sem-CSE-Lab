#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0;
int readers = 0;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex);//wait(mutex)
  readers = readers + 1;
  if(readers==1)
   sem_wait(&writeblock);//wait(writer)
  sem_post(&mutex);//signal(mutex)
  sleep(1);
  printf("Data for reader %d is %d\n",f,data);
  //data++;1111
  sem_wait(&mutex);//wait(mutex)
  readers = readers - 1;
  if(readers==0)
   sem_post(&writeblock);//signal(writer)
  sem_post(&mutex);//signal(mutex)
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);//wait(writer)
  data++;
    sleep(1);

  printf("Data Written by %d is %d\n",f,data);
  sem_post(&writeblock);//signal(writer)
}

int main()
{
  int i,b; 
  pthread_t rtid[5],wtid[5];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  for(i=0;i<=2;i++)
  {
    pthread_create(&wtid[i],NULL,writer,(void *)i);
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=2;i++)
  {
    pthread_join(wtid[i],NULL);
    pthread_join(rtid[i],NULL);
  }
  return 0;
}
