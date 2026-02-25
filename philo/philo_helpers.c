/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:19:30 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 13:19:55 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_over(t_philo *philo)
{
	bool	flag;

	pthread_mutex_lock(&philo->data->dead_lock);
	flag = (philo->data->dead_flag == STATUS_DEAD);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (flag);
}

void	print_action(t_philo *philo, char *message)
{
	long	timestamp;

	if (is_simulation_over(philo))
		return ;
	timestamp = (get_current_ustime() - philo->data->start_time) / 1000;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!is_simulation_over(philo))
		printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->write_lock);
}
