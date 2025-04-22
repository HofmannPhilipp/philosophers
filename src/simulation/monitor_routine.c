/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 14:37:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	observe_philosophers(t_table *table, long num_philo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < num_philo && !is_simulation_finished(table))
	{
		philo = table->philos[i];
		if (is_dead(philo, table))
		{
			print_status(philo,
				get_elapsed_time(get_long(&philo->philo_mutex,
						&table->start_time)), DEAD);
			set_bool(&table->table_mutex, &table->simulation_finished, true);
			return (true);
		}
		i++;
		usleep(500);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	long	num_philo;

	table = (t_table *)arg;
	increase_threads_ready(table);
	set_long(&table->table_mutex, &table->start_time, get_time());
	num_philo = get_long(&table->table_mutex, &table->data->num_philo);
	wait_all_threads(table);
	while (!is_simulation_finished(table))
	{
		if (observe_philosophers(table, num_philo))
			return (NULL);
	}
	return (NULL);
}
