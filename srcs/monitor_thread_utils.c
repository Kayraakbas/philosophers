/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/20 19:38:44 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_check_philo_death(t_philo *philo)
{
	long	current_time;
	long	last_meal;
	bool	is_dead;

	current_time = get_time_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal_time;
	is_dead = (current_time - last_meal > philo->resources->time_to_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (is_dead);
}

bool	safe_check_is_meal_finished(t_philo *philo)
{
	bool	meal_finished;

	pthread_mutex_lock(&philo->meal_mutex);
	meal_finished = (philo->meals_eaten
			>= philo->resources->num_of_each_philos_must_eat);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meal_finished);
}

void	time_monitor(t_philo *philos)
{
	int			i;
	t_resources	*resources;

	resources = philos->resources;
	i = 0;
	while (i < resources->num_of_philos)
	{
		if (safe_check_philo_death(&philos[i]))
		{
			safe_print(&philos[i], "died");
			pthread_mutex_lock(&resources->death_mutex);
			resources->simulation_ended = true;
			pthread_mutex_unlock(&resources->death_mutex);
			break ;
		}
		i++;
	}
}

void	meal_monitor(t_philo *philos)
{
	int			i;
	int			count;
	t_resources	*resources;

	resources = philos->resources;
	i = 0;
	count = 0;
	while (i < philos->resources->num_of_philos)
	{
		if (philos[i].resources->num_of_each_philos_must_eat > 0
			&& safe_check_is_meal_finished(&philos[i]))
			count++;
		i++;
	}
	if (count == resources->num_of_philos)
	{
		safe_print(philos, "meals finished");
		pthread_mutex_lock(&resources->death_mutex);
		resources->simulation_ended = true;
		pthread_mutex_unlock(&resources->death_mutex);
		return ;
	}
}

void	*death_monitor(void *arg)
{
	t_resources	*resources;
	t_philo		*philos;

	resources = (t_resources *)arg;
	philos = resources->philos;
	while (!is_sim_ended(philos))
	{
		time_monitor(philos);
		if (resources->num_of_each_philos_must_eat != -1)
			meal_monitor(philos);
	}
	return (NULL);
}
