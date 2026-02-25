/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:56:41 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 13:02:29 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_current_ustime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

int	monitored_sleep(long wait_time_ms, t_data *data)
{
	long	start;

	(void)data;
	start = get_current_ustime();
	while (((get_current_ustime() - start)) < wait_time_ms * 1000)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead_flag == STATUS_DEAD)
		{
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		usleep(500);
	}
	return (0);
}
