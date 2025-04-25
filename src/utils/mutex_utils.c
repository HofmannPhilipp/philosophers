/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:42:58 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 13:25:25 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Failed to init mutex\n");
		mutex = NULL;
		return (false);
	}
	return (true);
}

void	destroy_mutex(pthread_mutex_t *mutex)
{
	int	ret;

	if (mutex == NULL)
		return ;
	ret = pthread_mutex_destroy(mutex);
	if (ret == EBUSY)
		printf("Error: Mutex is still locked or in use\n");
	if (ret == EINVAL)
		printf("Error: Mutex is invalid (not initialized or corrupted)\n");
	else if (ret != 0)
		printf("Unknown error: %d\n", ret);
}

void	destroy_all_mutex(t_table *table, long length)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < length)
	{
		philo = table->philos[i];
		if (philo->philo_thread_created)
		{
			destroy_mutex(&philo->philo_mutex);
			destroy_mutex(&philo->philo_full_mutex);
			destroy_mutex(&philo->l_fork_mutex);
			destroy_mutex(&philo->last_meal_time_mutex);
		}
		i++;
	}
	if (table->monitor_thread_created)
	{
		destroy_mutex(&table->print_mutex);
		destroy_mutex(&table->table_data_mutex);
		destroy_mutex(&table->simulation_mutex);
		destroy_mutex(&table->start_time_mutex);
	}
}
