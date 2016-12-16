#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include </usr/include/semaphore.h>
#include <unistd.h>

#define BUFF_SIZE   5           
#define NP          2           
#define NC          2           
#define NITEMS      100         

typedef struct            
{
    int buf[BUFF_SIZE];   
    int in;               
    int out;              
    sem_t full;           
    sem_t empty;          
    pthread_mutex_t mutex;          
} sbuf_t;

sbuf_t shared;


void *Producer(void *arg) 
{
int i, item, index;
index = (int)arg;          
for (i=0; i < NITEMS; i++)
{
    item = i;                                           
    sem_wait(&shared.empty);                
    pthread_mutex_lock(&shared.mutex);      
    shared.buf[shared.in] = item;
    shared.in = (shared.in+1)%BUFF_SIZE; 
    printf("[P%d] Producing %d ...\n", index, item);
    fflush(stdout); 
    pthread_mutex_unlock(&shared.mutex);
    sem_post(&shared.full);

    if (i % 2 == 1) sleep(1);   


}
return NULL;
}

void *Consumer(void *arg)
{
    int i, item, index;
    index = (int)arg;
    for (i=NITEMS; i > 0; i--) {
        sem_wait(&shared.full);
        pthread_mutex_lock(&shared.mutex);
        item=i;
        item=shared.buf[shared.out];
        shared.out = (shared.out+1)%BUFF_SIZE;
        printf("[C%d] Consuming  %d ...\n", index, item);
        fflush(stdout);
        pthread_mutex_unlock(&shared.mutex);
        sem_post(&shared.empty);
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t idP, idC;  
    int index;

    sem_init(&shared.full, 0, 0);  
    sem_init(&shared.empty, 0, BUFF_SIZE);
    pthread_mutex_init(&shared.mutex, NULL);
    for (index = 0; index < NP; index++)
    {
        pthread_create(&idP, NULL, Producer, (void*)index);
    }
    for(index=0; index<NC; index++)
    {
        pthread_create(&idC, NULL, Consumer, (void*)index);
    }



    pthread_exit(NULL);
}
