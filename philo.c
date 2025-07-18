/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/18 17:46:40 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args			params;
	t_resources		resources;
	t_philo			*philo_arr;
	pthread_t		monitor_thread;
	int				i;

	if (check_arguments(argc, argv) == false)
		exit(1);
	params = convert_args_to_int(argv, argc);
	resources = init_resources(params);
	philo_arr = create_philo_arr(resources.num_of_philos, &resources);
	resources.philos = philo_arr;
	pthread_create(&monitor_thread, NULL, death_monitor, &resources);
	i = 0;
	while (i < resources.num_of_philos)
	{
		pthread_join(philo_arr[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	resources.simulation_ended = true;
	safe_free_all(resources);
	return (0);
}
