/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/18 00:00:00 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_args
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_each_philos_must_eat;
}	t_args;

typedef struct s_resources
{
	long			start_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_each_philos_must_eat;
	pthread_mutex_t	*locks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	bool			simulation_ended;
	struct s_philo	*philos;
}	t_resources;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	meal_mutex;
	t_resources		*resources;
	long			last_meal_time;
	int				meals_eaten;
}	t_philo;

long long		ft_atoll(const char *str);
int				ft_isdigit(int c);

pthread_mutex_t	*create_mutex_arr(int num_of_forks);
t_philo			*create_philo_arr(int num_of_philos, t_resources *resources);
void			set_philo(t_philo *philo, int id, int num_of_philos,
					t_resources *resources);
void			*philo_starter(void *arg);
t_resources		init_resources(t_args args);
bool			check_arguments(int ac, char **argv);
bool			check_overflow(char **argv);
t_args			convert_args_to_int(char **argv, int ac);
void			*time_to_eat(void *arg);
void			*time_to_sleep(void *arg);
void			*time_to_think(void *arg);
long			get_time_ms(void);
void			*death_monitor(void *arg);
void			acquire_forks(t_philo *philo);
void			release_forks(t_philo *philo);
void			meal_monitor(t_philo *philos);
void			time_monitor(t_philo *philos);
bool			is_sim_ended(t_philo *philo);
void			safe_print(t_philo *philo, char *content);
void			safe_sleep(long sleep_timer);
void			safe_free_all(t_resources resources);
bool			safe_check_philo_death(t_philo *philo);
bool			safe_check_is_meal_finished(t_philo *philo);

#endif