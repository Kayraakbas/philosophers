#include "philo.h"

long get_time_ms(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

bool is_sim_ended(t_philo *philo)
{
    bool result;
    pthread_mutex_lock(&philo->resources->death_mutex);
    result = philo->resources->simulation_ended;
    pthread_mutex_unlock(&philo->resources->death_mutex);
    return result;
}

void safe_print(t_philo *philo, char *content)
{
    long current_time;
    
    current_time = get_time_ms();
    pthread_mutex_lock(&philo->resources->print_mutex);
    if (is_sim_ended(philo) == false)
        printf("%ld %d %s\n", current_time - philo->resources->start_time, philo->id, content);
    pthread_mutex_unlock(&philo->resources->print_mutex);    

}

void safe_sleep(long sleep_timer)
{
    long start = get_time_ms();

    while (get_time_ms() - start < sleep_timer)
    {
        usleep(10);
    }
}