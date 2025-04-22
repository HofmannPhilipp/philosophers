/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:16:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 15:28:40 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_all_threads(t_philo **philos, t_table *table)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = get_time();
	set_long(&table->table_mutex, &table->start_time, start_time);
	while (i < table->data->num_philo)
	{
		set_long(&philos[i]->philo_mutex, &philos[i]->last_meal_time, start_time);
		pthread_create(&philos[i]->thread, NULL, &philo_routine, philos[i]);
		i++;
	}
	pthread_create(&table->monitor, NULL, &monitor_routine, table);
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
	set_bool(&table->table_mutex, &table->simulation_finished, true);
	pthread_join(table->monitor, NULL);
}

static void	destroy_all_mutex(t_philo **philos, t_table *table)
{
	int		i;
	long	num_philo;

	i = 0;
	num_philo = get_long(&table->table_mutex, &table->data->num_philo);
	while (i < num_philo)
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
	join_all_threads(philos, table);
	destroy_all_mutex(philos, table);
}
