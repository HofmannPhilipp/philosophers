/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:00:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/17 10:48:45 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, long ms, char *status)
{
	t_table *table;

	table = philo->table;
	if (get_bool(&philo->philo_mutex, &philo->full) || is_simulation_finished(philo->table))
		return ;
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d %s\n", ms, philo->id, status);
	pthread_mutex_unlock(&table->print_mutex);
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
	long	now;
	
	now = get_time();
	return (now - time);
}
void	print_philos_arr(t_philo **philo, int count)
{
	int	i = 0;

	while (i < count)
	{
		printf("🧠 Philosopher Info [ID: %d]\n", philo[i]->id);
		printf("────────────────────────────────────────────\n");
		printf("🍼 Birthday:           %ld\n", philo[i]->table->start_time);
		printf("🍝 Last meal time:     %ld\n", philo[i]->last_meal_time);
		printf("🍴 Meals eaten:        %ld\n", philo[i]->meals_eaten);
		printf("✅ Full:               %s\n", philo[i]->full ? "Yes" : "No");
		printf("🧵 Thread ID:          %lu\n", (unsigned long)philo[i]->thread);
		printf("🔐 Left fork mutex:    %p\n", (void *)&philo[i]->l_fork_mutex);
		printf("🔐 Right fork mutex:   %p\n", (void *)philo[i]->r_fork_mutex);
		printf("🏛️ Table pointer:      %p\n", (void *)philo[i]->table);
		printf("\n");

		i++;
	}
}

void	free_philos_arr(t_philo **philos, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

