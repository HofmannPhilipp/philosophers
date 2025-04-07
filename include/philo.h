/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:30 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/07 17:29:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK 		"is thinking"
# define DEAD		"died"

typedef struct s_table
{
	int	num_philo;
	int	num_meals;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	waiter_mutex;
}				t_table;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	long			bday;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*r_fork_mutex;
}				 t_philo;



void	philo_loop(t_philo **philos);

//init
t_table	*create_table(int num_philo, int die_time, int eat_time, int sleep_time, int num_meals);
t_philo	*create_philo(int id, t_table *table);
t_philo	**create_philos(t_table *table);
void	init_right_forks(t_philo **philos);

//actions
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);

//utils
void	hanlde_error(char *msg);
void	print_usage_error();
long	get_curr_time(long bday);
long	get_bday(void);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	print_arr(t_philo **arr);
void	print_msg(int id, long ms, char *str);
void	print_philo(t_philo *philo);

#endif