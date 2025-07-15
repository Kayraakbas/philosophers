#include "philo.h"

int main(int argc, char **argv)
{
    t_args params;
    t_resources resources;
    pthread_mutex_t *forks;
    t_philo *philo_arr;
    pthread_t monitor_thread;
    
    if (check_arguments(argc, argv) == false)
        exit(1);
    params = convert_args_to_int(argv, argc);
    resources =  init_resources(params);
    resources.start_time = get_time_ms();
    
    forks = create_mutex_arr(resources.num_of_philos);
    philo_arr = create_philo_arr(resources.num_of_philos, forks, &resources);
    resources.philos = philo_arr;

    pthread_create(&monitor_thread, NULL, death_monitor, &resources);
    
    // Wait for all philosopher threads to finish
    int i = 0;
    while (i < resources.num_of_philos)
    {
        pthread_join(philo_arr[i].thread, NULL);
        i++;
    }
    
    // Signal monitor to stop and wait for it
    resources.simulation_ended = true;
    pthread_join(monitor_thread, NULL);

    free(philo_arr);
    free(forks);

    return 0;
}