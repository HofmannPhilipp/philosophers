/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:16:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/14 10:59:00 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_philo **philos, t_table *table)
{
	create_all_threads(philos, table);
}

int	create_all_threads(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while(philos[i] != NULL)
	{
		pthread_create(&philos[i]->thread, NULL, &philo_routine, philos[i]);
		i++;
	}
	set_bool(&table->table_mutex, table->all_threads_ready, true);
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}
void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_ready))
	;
}

void	destroy_all_mutex(t_philo **philos)
{
	int	i;
	
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_mutex_destroy(&philos[i]->l_fork_mutex);
		i++;
	}
}
