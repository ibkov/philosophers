# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

int mail = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mail++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t p1,p2,p3,p4;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);
    pthread_create(&p3, NULL, &routine, NULL);
    pthread_create(&p4, NULL, &routine, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d", mail);
    return (0);


}