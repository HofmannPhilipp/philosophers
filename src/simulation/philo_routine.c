/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:15:41 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 09:59:21 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_simulation_start(t_table *table)
{
	while (!get_bool(&table->simulation_mutex, &table->simulation_start))
		;
}

static void	thinking(t_philo *philo)
{
	print_status(philo, THINK);
}

static void	sleeping(t_philo *philo, t_table *table)
{
	print_status(philo, SLEEP);
	usleep_plus(table->data->sleep_time);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	increment_threads_running(table);
	wait_simulation_start(table);
	if (get_long(&table->table_data_mutex, &table->data->num_philo) == 1)
	{
		one_philo(philo, table);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_simulation_finished(table))
	{
		if (is_full(philo, table))
			break ;
		eating(philo, table);
		sleeping(philo, table);
		thinking(philo);
	}
	return (NULL);
}
