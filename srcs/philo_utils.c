#include "philo.h"
// TO-DO implement free function for mutex arr
pthread_mutex_t *create_mutex_arr(int num_of_forks)
{
    int i;
    pthread_mutex_t *locks;
    if(num_of_forks <= 0)
        return NULL;
    locks = calloc(num_of_forks, sizeof(pthread_mutex_t));
    i = 0;
    if(!locks)
        return NULL;
    while (i < num_of_forks)
    {
        pthread_mutex_init(&locks[i], NULL);
        i++;
    }
    
    return locks;
}
void *philo_starter(int id)
{
    printf("philosopher: %d started\n",id);
    pthread_exit(NULL);
    return NULL;
}

void set_philo(t_philo *philo, int id, pthread_mutex_t *forks)
{
    philo->id = id;
    philo->left = &forks[id];
    philo->right = &forks[id];
    pthread_create(&philo->thread,NULL, philo_starter(philo->id), NULL);
}

t_philo *create_philo_arr(int num_of_philos, pthread_mutex_t *forks)
{
    t_philo *philos;
    int i;
    if (num_of_philos <= 0)
        return NULL;

    philos = calloc((num_of_philos + 1),  sizeof(t_philo));
    i = 0;
    while (&philos[i])
    {
        set_philo(&philos[i], i, forks);
        i++;
    }
    return philos;
}

t_resources init_resources(t_args args)
{
    t_resources resource;

    resource.locks = create_mutex_arr(args.num_of_philos);
    resource.time_to_eat = args.time_to_eat;
    resource.time_to_sleep = args.time_to_sleep;
    resource.time_to_die = args.time_to_die;
    resource.num_of_each_philos_must_eat = args.num_of_each_philos_must_eat;

    return resource;
}
