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
t_philo *create_philo_arr(int num_of_philos, pthread_mutex_t *forks)
{
    t_philo *philos;

 


    return philos;

}

t_philo init_philo(t_philo *t_philo, int id, pthread_mutex_t *forks)
{

}

void init_resources(t_resources resource, int num_of_philos, int t_to_eat, int t_to_sleep, int t_to_think, int each_philos_must_eat)
{
    resource.locks = create_mutex_arr(num_of_philos);
    resource.time_to_eat = t_to_eat;
    resource.time_to_sleep = t_to_sleep;
    resource.time_to_think = t_to_think;
    resource.each_philos_must_eat = each_philos_must_eat;
}
