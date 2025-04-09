/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/09 14:24:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hanlde_error(char *msg)
{
	if (msg)
		printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	print_msg(t_philo *philo, long ms, char *str)
{
	if (philo->table->dead == 1)
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", ms, philo->id, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_usage_error()
{
	printf("Error: Invalid number of arguments.\n");
	printf("Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

void	print_arr(t_philo **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("id: %d\n", arr[i]->id);
		i++;
	}
}

long	get_curr_time(long time)
{
	struct timeval tv;
	long	now;
	
	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now - time);
}

long	get_start_time(void)
{
	struct timeval tv;
	long	time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	print_philo(t_philo *philo)
{
	printf("🧠 Philosopher Info [ID: %d]\n", philo->id);
	printf("──────────────────────────────\n");
	printf("🍼 Birthday:           %ld\n", philo->start_time);
	printf("🍝 Last meal time:     %ld\n", philo->last_meal_time);
	printf("🍴 Meals eaten:        %d\n", philo->meals_eaten);
	printf("🧵 Thread ID:          %lu\n", (unsigned long)philo->thread);
	printf("🔐 Left fork mutex:    %p\n", (void *)&philo->l_fork_mutex);
	printf("🔐 Right fork mutex:   %p\n", (void *)philo->r_fork_mutex);
	printf("\n");
}

int	is_dead(t_philo *philo)
{
	if (get_curr_time(philo->last_meal_time) < philo->table->die_time)
		return (0);
	pthread_mutex_lock(&philo->table->dead_mutex);
	print_msg(philo, get_curr_time(philo->start_time), DEAD);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (1);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	print_msg(philo, get_curr_time(philo->start_time), FORK);
	pthread_mutex_lock(philo->r_fork_mutex);
	print_msg(philo, get_curr_time(philo->start_time), FORK);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork_mutex);
	pthread_mutex_unlock(philo->r_fork_mutex);
}
int	is_full(t_philo *philo)
{
	if (philo->meals_eaten < philo->table->num_meals)
		return (0);
	return (1);
}

int	parse_input(t_table *table, char *argv[])
{
	long	num_philo;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	num_meals;
	
	num_philo = ft_atol(argv[0]);
	die_time = ft_atol(argv[1]);
	eat_time = ft_atol(argv[2]);
	sleep_time = ft_atol(argv[3]);
	if (argv[4])
	{
		num_meals = ft_atol(argv[4]);
		if (!valid_inputs(num_philo, die_time, eat_time, sleep_time, num_meals))
			return (false);
 	}
	else
		table->num_meals = INT_MIN;
	table->num_philo = (int)num_philo;
	table->die_time = (int)die_time;
	table->eat_time = (int)eat_time;
	table->sleep_time = (int)sleep_time;
	return (true);
}

int	valid_inputs(long num_philo, long die_time, long eat_time, long sleep_time, long num_meals)
{
	if (num_philo == INT_MIN || die_time == INT_MIN ||
		eat_time == INT_MIN || sleep_time == INT_MIN)
	{
		printf("Invalid (non-numeric or out-of-range) input\n");
		return (false);
	}if (num_philo < 1 || num_philo > INT_MAX)
	{
		printf("Invalid number of philosophers\n");
		return (false);
	}
	if (die_time > INT_MAX || die_time < 60 ||
		eat_time > INT_MAX || eat_time < 60 ||
		sleep_time > INT_MAX || sleep_time < 60)
	{
		printf("Time values must be between 60 and INT_MAX\n");
		return (false);
	}
	if (num_meals == INT_MIN || num_meals < 1 || num_meals > INT_MAX)
		{
			printf("Invalid number of meals\n");
			return (false);
		}
	return (true);
}
