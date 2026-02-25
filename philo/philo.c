/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:56:28 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 14:00:12 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork");
	monitored_sleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->l_fork);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	eating_cycle(t_philo *philo)
{
	long	think_time;

	take_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_ustime();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	monitored_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_action(philo, "is sleeping");
	monitored_sleep(philo->data->time_to_sleep, philo->data);
	print_action(philo, "is thinking");
	if (philo->data->philo_num % 2 != 0)
	{
		think_time = philo->data->time_to_eat - philo->data->time_to_sleep;
		if (think_time < 0)
			think_time = 0;
		monitored_sleep(think_time + 1, philo->data);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000 / 2);
	if (philo->data->philo_num == 1)
		return (handle_single_philosopher(philo), NULL);
	while (!is_simulation_over(philo))
		eating_cycle(philo);
	return (NULL);
}
