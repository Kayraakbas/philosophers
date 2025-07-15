#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

typedef struct s_args
{
    int num_of_philos;
    int time_to_die; 
    int time_to_eat;
    int time_to_sleep;
    int num_of_each_philos_must_eat;
} t_args;

typedef struct s_resources
{
    long start_time;
    int num_of_philos;
    int time_to_die; 
    int time_to_eat;
    int time_to_sleep;
    int num_of_each_philos_must_eat;
    pthread_mutex_t *locks;
} t_resources;


typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    t_resources *resources;
} t_philo;

long long   ft_atoll(const char *str);
void        *ft_calloc(size_t count, size_t size);
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

// Philosopher utility functions
pthread_mutex_t *create_mutex_arr(int num_of_forks);
t_philo *create_philo_arr(int num_of_philos, pthread_mutex_t *forks, t_resources *resources);
void set_philo(t_philo *philo, int id, pthread_mutex_t *forks, int num_of_philos, t_resources *resources);
void *philo_starter(void *arg);
t_resources init_resources(t_args args);
bool check_arguments(int ac, char **argv);
bool  check_overflow(char **argv);
t_args convert_args_to_int(char **argv);
void *time_to_eat(void *arg);
void *time_to_sleep(void *arg);
void *time_to_think(void *arg);
long get_time_ms(void);



#endif