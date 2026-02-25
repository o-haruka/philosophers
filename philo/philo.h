/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:56:34 by homura            #+#    #+#             */
/*   Updated: 2026/02/24 13:29:40 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_MEALS_UNDEFINED -1
# define SUCCESS 0
# define ERROR 1
# define ERROR_MALLOC 2

// Simulation status
# define STATUS_ALIVE 0
# define STATUS_DEAD 1

typedef struct s_data
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;

	long			start_time;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}					t_philo;

// init.c
int					init_data(t_data *data, int argc, char **argv);
int					init_philos(t_philo **philos, t_data *data);

// utils.c
long				ft_atol(const char *str);
long				get_current_ustime(void);
int					monitored_sleep(long milliseconds, t_data *data);

// philo.c
void				*philo_routine(void *arg);

// philo helpers
bool				is_simulation_over(t_philo *philo);
void				print_action(t_philo *philo, char *message);

// monitor.c
void				*monitor_routine(void *arg);
#endif