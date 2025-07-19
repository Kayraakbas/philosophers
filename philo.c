/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/19 17:13:28 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void handle_1_philo(t_philo philo, t_resources resources)
{
	safe_sleep(resources.time_to_die);
	safe_print(&philo, "died");
	safe_free_all(resources);
	exit(1);
}

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
	if (resources.num_of_philos == 1)
		handle_1_philo(philo_arr[0], resources);
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
