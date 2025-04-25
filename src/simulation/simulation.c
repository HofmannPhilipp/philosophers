/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:16:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 10:33:20 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_all_threads(t_philo **philos, t_table *table)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = get_time();
	table->start_time = start_time;
	while (i < table->data->num_philo)
	{
		philos[i]->last_meal_time = start_time;
		if (pthread_create(&philos[i]->thread, NULL, &philo_routine,
				philos[i]) != 0)
		{
			printf("Error: Failed to create Philo Thread %d\n", i);
			philos[i]->philo_thread_created = false;
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &monitor_routine, table) != 0)
	{
		printf("Error: Failed to create Monitor Thread %d\n", i);
		table->monitor_thread_created = false;
	}
}

static void	join_all_threads(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->num_philo)
	{
		if (philos[i]->philo_thread_created)
			pthread_join(philos[i]->thread, NULL);
		i++;
	}
	set_bool(&table->simulation_mutex, &table->simulation_finished, true);
	if (table->monitor_thread_created)
		pthread_join(table->monitor, NULL);
}

void	start_simulation(t_philo **philos, t_table *table)
{
	create_all_threads(philos, table);
	join_all_threads(philos, table);
	destroy_all_mutex(table, table->data->num_philo);
}
