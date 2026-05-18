#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex1;
sem_t emptySlots;
sem_t full;

void* producer(void* arg)
{
    for(int i = 1; i <= 10; i++)
    {
        sem_wait(&emptySlots);

        pthread_mutex_lock(&mutex1);

        buffer[count] = i;
        cout << "Produced: " << i << endl;

        count++;

        pthread_mutex_unlock(&mutex1);

        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    for(int i = 1; i <= 10; i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&mutex1);

        int item = buffer[count - 1];
        count--;

        cout << "Consumed: " << item << endl;

        pthread_mutex_unlock(&mutex1);

        sem_post(&emptySlots);

        sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t p, c;

    pthread_mutex_init(&mutex1, NULL);

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&mutex1);

    sem_destroy(&emptySlots);
    sem_destroy(&full);

    return 0;
}