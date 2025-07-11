#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_resources
{
    int time_to_think; 
    int time_to_eat;
    int time_to_sleep;
    int each_philos_must_eat;
    pthread_mutex_t *locks;
} t_resources;


typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
} t_philo;

#endif