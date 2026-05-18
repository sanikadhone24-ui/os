#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define N 5

sem_t chopstick[N];

void* philosopher(void* num)
{
    int id = *(int*)num;

    cout << "Philosopher " << id << " is thinking" << endl;
    sleep(1);

    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % N]);

    cout << "Philosopher " << id << " is eating" << endl;
    sleep(2);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % N]);

    cout << "Philosopher " << id << " finished eating" << endl;

    pthread_exit(NULL);
}

int main()
{
    pthread_t p[N];
    int phil[N];

    for(int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for(int i = 0; i < N; i++)
    {
        phil[i] = i + 1;
        pthread_create(&p[i], NULL, philosopher, &phil[i]);
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    for(int i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}