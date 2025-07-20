/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/20 19:36:54 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*create_mutex_arr(int num_of_forks)
{
	int				i;
	pthread_mutex_t	*locks;

	if (num_of_forks <= 0)
		return (NULL);
	locks = malloc((num_of_forks) * sizeof(pthread_mutex_t));
	i = 0;
	if (!locks)
		return (NULL);
	while (i < num_of_forks)
	{
		pthread_mutex_init(&locks[i], NULL);
		i++;
	}
	return (locks);
}

void	*philo_starter(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_sim_ended(philo))
	{
		acquire_forks(philo);
		time_to_eat(philo);
		release_forks(philo);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return (NULL);
}

void	set_philo(t_philo *philo, int id, int num_of_philos,
		t_resources *resources)
{
	philo->id = id;
	philo->left = &resources->locks[id];
	philo->right = &resources->locks[(id + 1) % num_of_philos];
	philo->resources = resources;
	philo->meals_eaten = 0;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_init(&philo->meal_mutex, NULL);
}

t_philo	*create_philo_arr(int num_of_philos, t_resources *resources)
{
	t_philo	*philos;
	int		i;

	if (num_of_philos <= 0)
		return (NULL);
	philos = malloc(num_of_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < num_of_philos)
	{
		set_philo(&philos[i], i, num_of_philos, resources);
		i++;
	}
	i = 0;
	usleep(500);
	while (i < num_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_starter,
			(void *)&philos[i]);
		i++;
	}
	return (philos);
}
