#include "philo.h"

/*void* foo()
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
    (void) arg;
    printf("Thread1 is running...\n");
    sleep(2);
    printf("Thread1 finished.\n");
    return NULL;
}*/

int main(int argc, char **argv)
{
    t_args params;
    t_resources resources;
    pthread_mutex_t *forks;
    t_philo *philo_arr;
    
    if (check_arguments(argc, argv) == false)
        exit(1);
    params = convert_args_to_int(argv);
    resources =  init_resources(params);
    printf("params :\n %d\n %d\n %d\n %d\n",resources.num_of_each_philos_must_eat, resources.time_to_die, resources.time_to_eat, resources.time_to_sleep);
    
    forks = create_mutex_arr(resources.num_of_philos);
    // start simulation
    if (!forks)
    {
        printf("forks not been initialized");
    }
    philo_arr = create_philo_arr(resources.num_of_philos, forks, &resources);
    if (!philo_arr)
    {
        printf("philos not been initialized");
    }

    free(philo_arr);
    free(forks);

    //input argumnents being taken correctly,
    //next steps will be creating forks and philos based on the params,
    //afterwards start to create a synvhronus algorithm that works
    //than make a propeer dining table algorthim subject wants from you

    /*pthread_t thread;
    pthread_t thread2;

    pthread_create(&thread2,NULL, foo2, NULL);
    pthread_create(&thread,NULL, myThreadFunc, NULL);


    pthread_join(thread, NULL);
    pthread_detach(thread);
    pthread_join(thread2, NULL);*/
    return 0;
}