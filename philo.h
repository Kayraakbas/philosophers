#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct s_philo
{
    pthread_t thread;

    int time_to_eat;
    int time_to_sleep;
    int notepme;
    pthread_mutex_t left;
    pthread_mutex_t right;

} t_philo;

#endif