/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:30 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/14 11:08:49 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK 		"is thinking"
# define DEAD		"died"

typedef struct s_data
{
	int	num_philo;
	int	num_meals;
	int	die_time;
	int	eat_time;
	int	sleep_time;
}	t_data;

typedef struct s_table
{
	t_data			*data;
	bool			is_dead;
	bool			simualtion_finished;
	bool			all_threads_ready;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
}				t_table;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	long			start_time;
	long			last_meal_time;
	int				meals_eaten;
	bool			has_both_forks;
	bool			full;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*r_fork_mutex;
}				 t_philo;


//init
int	init_table(t_table *table, t_data *data);
t_philo	*create_philo(int id, t_table *table);
t_philo	**create_philos(t_table *table);

//actions
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
bool	is_dead(t_philo *philo);
bool	is_full(t_philo *philo);
void	*philo_routine(void *arg);

void	wait_all_threads(t_table *table);

//utils
void	set_bool(pthread_mutex_t *mutex,bool *ptr, bool new_value);
bool	get_bool(pthread_mutex_t *mutex, bool *ptr);
long	get_long(pthread_mutex_t *mutex, long *ptr);
bool	is_simulation_finished(t_table *table);
void	print_usage_error();
long	get_elapsed_time(long bday);
long	get_time(void);
long	ft_atol(const char *str);
void	print_msg(t_philo *philo, long ms, char *str);
void	print_philo(t_philo *philo);
int		parse_input(t_data *data, char *argv[]);

#endif