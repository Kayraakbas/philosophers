/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by omakbas           #+#    #+#             */
/*   Updated: 2025/07/19 17:15:36 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_int_check(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_arguments(int ac, char **argv)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("invalid arg count: you have entered %d arguments\n", ac);
		printf("example argument format: ./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_int_check(argv[i]) == false)
		{
			printf("int check fault wrong arg: %d, %s\n", i, argv[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_overflow(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoll(argv[i]) > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

t_args	convert_args_to_int(char **argv, int ac)
{
	t_args	params;

	if (!argv || !*argv)
		exit(1);
	if (check_overflow(argv) == false)
	{
		printf("overflow error;\n");
		exit(1);
	}
	params.num_of_philos = (int) atoll(argv[1]);
	params.time_to_die = (int) atoll(argv[2]);
	params.time_to_eat = (int) atoll(argv[3]);
	params.time_to_sleep = (int) atoll(argv[4]);
	params.num_of_each_philos_must_eat = -1;
	if (ac == 6)
		params.num_of_each_philos_must_eat = (int) atoll(argv[5]);
	return (params);
}

t_resources	init_resources(t_args args)
{
	t_resources	resource;

	resource.start_time = get_time_ms();
	resource.num_of_philos = args.num_of_philos;
	resource.locks = create_mutex_arr(args.num_of_philos);
	resource.time_to_eat = args.time_to_eat;
	resource.time_to_sleep = args.time_to_sleep;
	resource.time_to_die = args.time_to_die;
	resource.num_of_each_philos_must_eat = args.num_of_each_philos_must_eat;
	resource.simulation_ended = false;
	resource.philos = NULL;
	pthread_mutex_init(&resource.print_mutex, NULL);
	pthread_mutex_init(&resource.death_mutex, NULL);
	return (resource);
}
