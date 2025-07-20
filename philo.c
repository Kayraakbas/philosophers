/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/20 14:00:02 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philosopher_threads(t_resources resources, t_philo *philo_arr)
{
	int	i;

	if (resources.num_of_philos == 1)
		pthread_detach(philo_arr[0].thread);
	else
	{
		i = 0;
		while (i < resources.num_of_philos)
		{
			pthread_join(philo_arr[i].thread, NULL);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_args			params;
	t_resources		resources;
	t_philo			*philo_arr;
	pthread_t		monitor_thread;

	if (check_arguments(argc, argv) == false)
		exit(1);
	params = convert_args_to_int(argv, argc);
	resources = init_resources(params);
	philo_arr = create_philo_arr(resources.num_of_philos, &resources);
	resources.philos = philo_arr;
	pthread_create(&monitor_thread, NULL, death_monitor, &resources);
	join_philosopher_threads(resources, philo_arr);
	pthread_join(monitor_thread, NULL);
	safe_free_all(resources);
	return (0);
}
