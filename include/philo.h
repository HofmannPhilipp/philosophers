/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:30 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/23 19:05:59 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define L_FORK "has taken a left fork"
# define R_FORK "has taken a right fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

# define NO_MEAL_LIMIT -1

typedef struct s_data
{
	long			num_philo;
	long			num_meals;
	long			die_time;
	long			eat_time;
	long			sleep_time;
}					t_data;

typedef struct s_table
{
	t_data			*data;
	bool			simulation_finished;
	long			start_time;
	bool			simulation_start;
	long			num_threads_running;
	pthread_t		monitor;
	struct s_philo	**philos;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	table_data_mutex;
	pthread_mutex_t	print_mutex;
}					t_table;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	long			last_meal_time;
	long			meals_eaten;
	bool			full;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	philo_full_mutex;
	pthread_mutex_t	last_meal_time_mutex;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*r_fork_mutex;
}					t_philo;

//init
bool				init_table(t_table *table, t_data *data);
t_philo				*create_philo(int id, t_table *table);
t_philo				**init_philos_arr(t_table *table);

//simulation
void				start_simulation(t_philo **philos, t_table *table);
void				*monitor_routine(void *arg);
void				*philo_routine(void *arg);
void				eating(t_philo *philo, t_table *table);

//simulation_utils
void				wait_all_threads(t_table *table);
void				set_start_time(t_table *table);
bool				is_dead(t_philo *philo, t_table *table);
bool				is_full(t_philo *philo, t_table *table);
void				usleep_plus(long duration, t_table *table);
void				one_philo(t_philo *philo, t_table *table);

//parse
bool				parse_input(t_data *data, char *argv[]);

//setters
void				set_bool(pthread_mutex_t *mutex, bool *ptr, bool new_value);
void				set_long(pthread_mutex_t *mutex, long *ptr, long new_value);
void				increase_threads_ready(t_table *table);

//getters
bool				get_bool(pthread_mutex_t *mutex, bool *ptr);
long				get_long(pthread_mutex_t *mutex, long *ptr);
bool				is_simulation_finished(t_table *table);

//utils
long				get_elapsed_time(long time);
long				get_time(void);
void				print_status(t_philo *philo, char *status);
void				print_usage_error(void);
void				free_philos_arr(t_philo **philos, int length);
long				ft_atol(const char *str);

#endif