/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:56:21 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 13:06:42 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Note: Death status=1~N (dynamic philosopher ID, used directly) */
#define MONITOR_CONTINUE 0
#define MONITOR_ALL_FINISHED -1

static int	check_death(t_philo *philos)
{
	int		i;
	long	current_time;
	long	last_meal;
	long	time_to_die;

	current_time = get_current_ustime();
	time_to_die = philos[0].data->time_to_die * 1000;
	i = 0;
	while (i < philos[0].data->philo_num)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		last_meal = philos[i].last_meal_time;
		pthread_mutex_unlock(&philos[i].meal_lock);
		if ((current_time - last_meal) >= time_to_die)
			return (i + 1);
		i++;
	}
	return (MONITOR_CONTINUE);
}

static int	check_meals_completed(t_philo *philos)
{
	int	i;
	int	finished_eating;

	if (philos[0].data->max_meals == MAX_MEALS_UNDEFINED)
		return (MONITOR_CONTINUE);
	finished_eating = 0;
	i = 0;
	while (i < philos[0].data->philo_num)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].data->max_meals)
			finished_eating++;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].data->philo_num)
	{
		pthread_mutex_lock(&philos[0].data->dead_lock);
		philos[0].data->dead_flag = STATUS_DEAD;
		pthread_mutex_unlock(&philos[0].data->dead_lock);
		return (1);
	}
	return (MONITOR_CONTINUE);
}

int	monitor_philosophers(t_philo *philos)
{
	int	death_result;

	death_result = check_death(philos);
	if (death_result != MONITOR_CONTINUE)
		return (death_result);
	if (check_meals_completed(philos) == 1)
		return (MONITOR_ALL_FINISHED);
	return (MONITOR_CONTINUE);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		monitor_result;
	long	death_time;

	philos = (t_philo *)arg;
	while (1)
	{
		monitor_result = monitor_philosophers(philos);
		if (monitor_result == MONITOR_ALL_FINISHED)
			break ;
		else if (monitor_result != MONITOR_CONTINUE)
		{
			pthread_mutex_lock(&philos[0].data->dead_lock);
			philos[0].data->dead_flag = STATUS_DEAD;
			pthread_mutex_unlock(&philos[0].data->dead_lock);
			death_time = (get_current_ustime() - philos[0].data->start_time)
				/ 1000;
			pthread_mutex_lock(&philos[0].data->write_lock);
			printf("%ld %d died\n", death_time, monitor_result);
			pthread_mutex_unlock(&philos[0].data->write_lock);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
