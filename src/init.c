/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 13:47:12 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_table(t_table *table, t_data *data)
{
	memset(table, 0, sizeof(t_table));
	table->data = data;
	table->monitor_thread_created = true;
	if (!create_mutex(&table->table_data_mutex))
		return (false);
	if (!create_mutex(&table->simulation_mutex))
		return (false);
	if (!create_mutex(&table->start_time_mutex))
		return (false);
	if (!create_mutex(&table->print_mutex))
		return (false);
	return (true);
}

t_philo	*create_philo(int id, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		printf("Error: Failed malloc philo\n");
		return (NULL);
	}
	memset(philo, 0, sizeof(t_philo));
	if (!create_mutex(&philo->philo_mutex))
		return (NULL);
	if (!create_mutex(&philo->philo_full_mutex))
		return (NULL);
	if (!create_mutex(&philo->last_meal_time_mutex))
		return (NULL);
	if (!create_mutex(&philo->l_fork_mutex))
		return (NULL);
	philo->id = id;
	philo->table = table;
	philo->philo_thread_created = true;
	return (philo);
}

static void	init_right_forks(t_philo **philos, t_table *table)
{
	int	i;

	if (table->data->num_philo == 1)
	{
		philos[0]->r_fork_mutex = NULL;
		return ;
	}
	i = 1;
	while (i < table->data->num_philo)
	{
		philos[i - 1]->r_fork_mutex = &philos[i]->l_fork_mutex;
		i++;
	}
	philos[i - 1]->r_fork_mutex = &philos[0]->l_fork_mutex;
}

t_philo	**create_philos_arr(t_table *table)
{
	int		i;
	t_philo	**philos_arr;
	t_philo	*philo;

	philos_arr = malloc(sizeof(t_philo *) * (table->data->num_philo));
	if (!philos_arr)
	{
		printf("Error: Failed malloc philos_arr\n");
		return (NULL);
	}
	table->philos = philos_arr;
	i = -1;
	while (++i < table->data->num_philo)
	{
		philo = create_philo(i + 1, table);
		if (!philo)
		{
			destroy_all_mutex(table, i);
			free_philos_arr(philos_arr, i);
			return (NULL);
		}
		philos_arr[i] = philo;
	}
	init_right_forks(philos_arr, table);
	return (philos_arr);
}
