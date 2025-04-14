/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/14 10:56:10 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, long ms, char *status)
{
	if (is_simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d %s\n", ms, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_usage_error()
{
	printf("Error: Invalid number of arguments.\n");
	printf("Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

long	get_time(void)
{
	struct timeval tv;
	long	time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	get_elapsed_time(long time)
{
	struct timeval tv;
	long	now;
	
	now = get_time();
	return (now - time);
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

bool	is_dead(t_philo *philo)
{
	if (get_elapsed_time(philo->last_meal_time) < philo->table->data->die_time)
		return (false);
	set_bool(&philo->table->table_mutex, philo->table->is_dead, true);
	print_msg(philo, get_elapsed_time(philo->start_time), DEAD);
	return (true);
}

bool	is_full(t_philo *philo)
{
	if (philo->meals_eaten < philo->table->data->num_meals)
		return (false);
	return (true);
}
// int	usleep_plus(long	duration, t_table *table)
// {
// 	long	start;

// 	start = get_time();
// 	while(gettime() - start < duration)
// 	{
		
// 	}
// }

