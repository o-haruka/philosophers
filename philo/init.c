/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:55:30 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 12:55:39 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_locks(t_data *data)
{
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->dead_lock);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (ERROR_MALLOC);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = MAX_MEALS_UNDEFINED;
	data->dead_flag = STATUS_ALIVE;
	if (init_locks(data) != SUCCESS)
		return (ERROR);
	if (init_forks(data) != SUCCESS)
	{
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->write_lock);
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!*philos)
		return (ERROR_MALLOC);
	i = 0;
	while (i < data->philo_num)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].data = data;
		(*philos)[i].l_fork = &data->forks[i];
		(*philos)[i].r_fork = &data->forks[(i + 1) % data->philo_num];
		if (pthread_mutex_init(&(*philos)[i].meal_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philos)[i].meal_lock);
			free(*philos);
			*philos = NULL;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
