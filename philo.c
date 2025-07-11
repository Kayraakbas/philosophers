#include "philo.h"

void* foo()
{
    printf("from thread 1\n");
    pthread_exit(NULL);
    
    printf("This will not be executed\n");
    return NULL;
}

void* foo2()
{
    printf("from thread 2\n");

    return NULL;
}

void* myThreadFunc(void* arg) {
    printf("Thread1 is running...\n");
    sleep(2);
    printf("Thread1 finished.\n");
    return NULL;
}

int main(int argc, char **argv)
{

    (void) argc;
    (void) argv;
    int num_of_philosophers = 5;
    int time_to_eat = 200;
    int time_to_sleep = 200;
    int time_to_die = 800;
    int notepme;
    
    pthread_t thread;
    pthread_t thread2;

    pthread_create(&thread2,NULL, foo2, NULL);
    pthread_create(&thread,NULL, myThreadFunc, NULL);


    pthread_join(thread, NULL);
    pthread_detach(thread);
    pthread_join(thread2, NULL);
    return 0;
}