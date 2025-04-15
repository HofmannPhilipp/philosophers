/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:31:33 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;
	long	philos_full_count;
	
	
	table = (t_table *)arg;
	wait_all_threads(table);
	philos_full_count = 0;
	while (1)
	{
		i = 0;
		while (i < table->data->num_philo)
		{
			philo = table->philos[i];
			if (is_dead(philo, table))
			{
				set_bool(&table->table_mutex, &table->simulation_finished, true);
				return (NULL);
			}
			if (is_full(philo, table))
				philos_full_count++;
			if (philos_full_count >= get_long(&table->table_mutex, &table->data->num_philo))
			{
				set_bool(&table->table_mutex, &table->simulation_finished, true);
				return (NULL);
			}
			i ++;
			usleep(500);
		}
	}
	return (NULL);
}