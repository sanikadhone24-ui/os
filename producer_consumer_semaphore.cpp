#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define SIZE 5

int buffer[SIZE];
int in = 0;
int out = 0;

sem_t emptySlots;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg)
{
    int item;

    for(int i = 1; i <= 5; i++)
    {
        item = i;

        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        cout << "Producer produced: " << item << endl;

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    int item;

    for(int i = 1; i <= 5; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        cout << "Consumer consumed: " << item << endl;

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);

        sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t p, c;

    sem_init(&emptySlots, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);

    return 0;
}