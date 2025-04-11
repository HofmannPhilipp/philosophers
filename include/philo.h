/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:30 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/11 15:18:30 by phhofman         ###   ########.fr       */
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
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
}				t_table;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	long			start_time;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	bool			has_both_forks;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*r_fork_mutex;
}				 t_philo;

void	philo_loop(t_philo **philos);

//init
int	init_table(t_table *table, t_data *data);
t_philo	*create_philo(int id, t_table *table);
t_philo	**create_philos(t_table *table);

//actions
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
int		is_dead(t_philo *philo);
int		is_full(t_philo *philo);

//utils
void	print_usage_error();
long	get_elapsed_time(long bday);
long	get_time(void);
long	ft_atol(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	print_arr(t_philo **arr);
void	print_msg(t_philo *philo, long ms, char *str);
void	print_philo(t_philo *philo);
int		parse_input(t_data *data, char *argv[]);

#endif