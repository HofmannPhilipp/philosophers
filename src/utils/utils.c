/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 10:05:12 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	t_table	*table;
	long	start_time;

	table = philo->table;
	if (get_bool(&philo->philo_full_mutex, &philo->full)
		|| is_simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(&table->print_mutex);
	if (!get_bool(&philo->philo_mutex, &philo->full)
		&& !is_simulation_finished(philo->table))
	{
		start_time = get_long(&table->start_time_mutex, &table->start_time);
		printf("%ld %d %s\n", get_elapsed_time(start_time), philo->id, status);
	}
	pthread_mutex_unlock(&table->print_mutex);
}

void	print_usage_error(void)
{
	printf("Error: Invalid number of arguments.\n");
	printf("Usage: ./philosophers num_philos die_time eat_time sleep_time \
		[num_meals]\n");
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	get_elapsed_time(long time)
{
	long	now;

	now = get_time();
	return (now - time);
}

void	free_philos_arr(t_philo **philos, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(philos[i]);
		philos[i] = NULL;
		i++;
	}
	free(philos);
}
