/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 09:56:32 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_simulation_clock(t_table *table)
{
	int		i;
	t_philo	*philo;
	long	num_philo;

	num_philo = get_long(&table->table_data_mutex, &table->data->num_philo);
	i = 0;
	set_long(&table->start_time_mutex, &table->start_time, get_time());
	while (i < num_philo)
	{
		philo = table->philos[i];
		set_long(&philo->last_meal_time_mutex, &philo->last_meal_time,
			get_time());
		i++;
	}
	set_bool(&table->simulation_mutex, &table->simulation_start, true);
}

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
			print_status(philo, DEAD);
			set_bool(&table->simulation_mutex,
				&table->simulation_finished, true);
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
	increment_threads_running(table);
	wait_all_threads(table);
	start_simulation_clock(table);
	num_philo = get_long(&table->table_data_mutex, &table->data->num_philo);
	while (!is_simulation_finished(table))
	{
		if (observe_philosophers(table, num_philo))
			return (NULL);
	}
	return (NULL);
}
