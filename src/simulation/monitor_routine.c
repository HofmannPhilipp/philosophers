/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/16 17:45:48 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;
	long	num_philo;
	
	table = (t_table *)arg;
	pthread_mutex_lock(&table->table_mutex);
	table->num_threads_ready++;
	pthread_mutex_unlock(&table->table_mutex);
	wait_all_threads(table);
	set_long(&table->table_mutex, &table->start_time, get_time());
	num_philo = get_long(&table->table_mutex, &table->data->num_philo);
	while (!is_simulation_finished(table))
	{
		i = 0;
		while (i < num_philo && !is_simulation_finished(table))
		{
			philo = table->philos[i];
			if (is_dead(philo, table))
			{
				print_status(philo, get_elapsed_time(get_long(&philo->philo_mutex, &table->start_time)), DEAD);
				set_bool(&table->table_mutex, &table->simulation_finished, true);
				return (NULL);
			}
			i ++;
			usleep(500);
		}
	}
	return (NULL);
}