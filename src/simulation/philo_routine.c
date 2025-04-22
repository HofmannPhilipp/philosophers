/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:15:41 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 14:35:44 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo, t_table *table)
{
	print_status(philo, get_elapsed_time(table->start_time), THINK);
}

static void	sleeping(t_philo *philo, t_table *table)
{
	print_status(philo, get_elapsed_time(table->start_time), SLEEP);
	usleep_plus(table->data->sleep_time, table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	increase_threads_ready(table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	if (get_long(&table->table_mutex, &table->data->num_philo) == 1)
	{
		one_philo(philo, table);
		return (NULL);
	}
	wait_all_threads(table);
	while (!is_simulation_finished(table))
	{
		if (is_full(philo, table))
		{
			set_bool(&philo->philo_mutex, &philo->full, true);
			break ;
		}
		thinking(philo, table);
		eating(philo, table);
		sleeping(philo, table);
	}
	return (NULL);
}
