#include "philo.h"


void acquire_forks(t_philo *philo)
{
    long current_time;
    
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left);
        current_time = get_time_ms();
        printf("%ld %d has taken a fork\n", current_time - philo->resources->start_time, philo->id);        
        pthread_mutex_lock(philo->right);
        current_time = get_time_ms();
        printf("%ld %d has taken a fork\n", current_time - philo->resources->start_time, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->right);
        current_time = get_time_ms();
        printf("%ld %d has taken a fork\n", current_time - philo->resources->start_time, philo->id);
        pthread_mutex_lock(philo->left);
        current_time = get_time_ms();
        printf("%ld %d has taken a fork\n", current_time - philo->resources->start_time, philo->id);
        
    }
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left);
    pthread_mutex_unlock(philo->right);
}

void *time_to_eat(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long current_time;
    
    current_time = get_time_ms();
    pthread_mutex_lock(&philo->resources->print_mutex);
    printf("%ld %d is eating\n", current_time - philo->resources->start_time, philo->id);
    pthread_mutex_unlock(&philo->resources->print_mutex);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_lock(&philo->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    usleep(philo->resources->time_to_eat * 1000);

    return NULL;
}

void *time_to_sleep(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long current_time;
    
    current_time = get_time_ms();
    pthread_mutex_lock(&philo->resources->print_mutex); 
    printf("%ld %d is sleeping\n", current_time - philo->resources->start_time, philo->id);
    pthread_mutex_unlock(&philo->resources->print_mutex); 
    usleep(philo->resources->time_to_sleep * 1000);
    
    return NULL;
}

void *time_to_think(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long current_time;
    
    current_time = get_time_ms();
    pthread_mutex_lock(&philo->resources->print_mutex);
    printf("%ld %d is thinking\n", current_time - philo->resources->start_time, philo->id);
    pthread_mutex_unlock(&philo->resources->print_mutex);
    usleep(philo->resources->time_to_die * 1000);

    return NULL;
}