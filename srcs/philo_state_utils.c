#include "philo.h"

void acquire_forks(t_philo *philo)
{   
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->right);
        safe_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->left);
        safe_print(philo, "has taken a fork");
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
    
    safe_print(philo, "is eating");
    pthread_mutex_lock(&philo->meal_mutex);
    philo->meals_eaten++;
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->meal_mutex);
    safe_sleep(philo->resources->time_to_eat);
    return NULL;
}

void *time_to_sleep(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    safe_print(philo, "is sleeping"); 
    safe_sleep(philo->resources->time_to_sleep);
    return NULL;
}

void *time_to_think(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    safe_print(philo, "is thinking");
    return NULL;
}
