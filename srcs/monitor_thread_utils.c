#include "philo.h"

void time_monitor (t_philo *philos)
{
    int i;
    long current_time;
    t_resources *resources = philos->resources; 
    i = 0;

    while (i < resources->num_of_philos)
    {
        current_time = get_time_ms();            
        if (current_time - philos[i].last_meal_time > resources->time_to_die)
        {
            pthread_mutex_lock(&resources->print_mutex);
            printf("%ld %d died (time monitor)\n", current_time - resources->start_time, philos[i].id);
            pthread_mutex_unlock(&resources->print_mutex);
                
            pthread_mutex_lock(&resources->death_mutex);
            resources->simulation_ended = true;
            pthread_mutex_unlock(&resources->death_mutex);
            return;
        }
        i++;
    }
}

void meal_monitor(t_philo *philos)
{
    int i;
    int count;
    t_resources *resources = philos->resources;

    i = 0;
    count = 0;
    while (i < philos->resources->num_of_philos)
    {
        if (philos[i].resources->num_of_each_philos_must_eat > 0 && 
         philos[i].meals_eaten >= philos[i].resources->num_of_each_philos_must_eat)
            count++;
        i++;
    }
    if (count == resources->num_of_philos)
    {
        pthread_mutex_lock(&resources->print_mutex);
        printf("%ld %d died meal monitor\n", get_time_ms() - resources->start_time, philos[i].id);
        pthread_mutex_unlock(&resources->print_mutex);
        pthread_mutex_lock(&resources->death_mutex);
        resources->simulation_ended = true;
        pthread_mutex_unlock(&resources->death_mutex);
        return;
    }
}

void *death_monitor(void *arg)
{
    t_resources *resources = (t_resources *)arg;
    t_philo *philos = resources->philos;

    while (!is_sim_ended(philos))
    {
        time_monitor(philos);
        if (resources->num_of_each_philos_must_eat != -1)
            meal_monitor(philos);
        safe_sleep(500);
    }
    return NULL;
}
