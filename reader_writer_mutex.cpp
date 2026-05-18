#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;

int readcount = 0;
int shared_data = 0;

void *reader(void *arg)
{
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex1);
    readcount++;

    if (readcount == 1)
        pthread_mutex_lock(&wrt);

    pthread_mutex_unlock(&mutex1);

    cout << "Reader " << id << " reads data = " << shared_data << endl;  

    pthread_mutex_lock(&mutex1);
    readcount--;

    if (readcount == 0)
        pthread_mutex_unlock(&wrt);

    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    pthread_mutex_lock(&wrt);

    shared_data++;
    cout << "Writer " << id << " writes data = " << shared_data << endl;

    pthread_mutex_unlock(&wrt);

    pthread_exit(NULL);
}

int main()
{
    pthread_t r[3], w[2];

    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    return 0;
}