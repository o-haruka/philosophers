/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:55:49 by homura            #+#    #+#             */
/*   Updated: 2026/02/25 17:51:11 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static int	validate_arguments(int argc, char *argv[])
{
	int		i;
	long	value;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid arguments\n"), ERROR);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (printf("Error: Args contains non-digit\n"), ERROR);
		value = ft_atol(argv[i]);
		if (value <= 0)
			return (printf("Error: Args must be digits only\n"), ERROR);
		if (value > INT_MAX)
			return (printf("Error: Args exceeds INT_MAX\n"), ERROR);
		i++;
	}
	return (SUCCESS);
}

static void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
}

static void	exit_simulation(t_data *data, t_philo *philos, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
		pthread_join(philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->forks);
	free(philos);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	monitor;
	int			i;
	t_philo		*philos;

	if (validate_arguments(argc, argv) != SUCCESS)
		return (ERROR);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (ERROR);
	if (init_philos(&philos, &data) != SUCCESS)
	{
		cleanup_data(&data);
		return (ERROR);
	}
	data.start_time = get_current_ustime();
	i = 0;
	while (i < data.philo_num)
	{
		philos[i].last_meal_time = data.start_time;
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, philos);
	exit_simulation(&data, philos, monitor);
	return (SUCCESS);
}
