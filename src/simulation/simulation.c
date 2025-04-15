/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:16:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:34:14 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_all_threads(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while(i < table->data->num_philo)
	{
		pthread_create(&philos[i]->thread, NULL, &philo_routine, philos[i]);
		i++;
	}
	// pthread_create(&table->monitor, NULL, &monitor_routine, table);
}

static void	join_all_threads(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->num_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	// pthread_join(table->monitor, NULL);
}
static void	destroy_all_mutex(t_philo **philos, t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->data->num_philo)
	{
		pthread_mutex_destroy(&philos[i]->l_fork_mutex);
		pthread_mutex_destroy(&philos[i]->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->table_mutex);
}

void	start_simulation(t_philo **philos, t_table *table)
{
	create_all_threads(philos, table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	join_all_threads(philos,table);
	destroy_all_mutex(philos, table);
}
