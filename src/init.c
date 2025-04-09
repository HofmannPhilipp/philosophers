/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/09 16:33:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, t_data *data)
{
	table->data = data;
	if(pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		printf("Failed to init print mutex\n");
		return (1);
	}
	if(pthread_mutex_init(&table->dead_mutex, NULL) != 0)
	{
		printf("Failed to init dead mutex\n");
		return (1);
	}
	return (0);
}

t_philo	*create_philo(int id, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_init(&philo->l_fork_mutex, NULL);
	philo->id = id + 1;
	philo->table = table;
	return (philo);
}

static void	init_right_forks(t_philo **philos)
{
	int	i;

	i = 1;
	while (philos[i] != NULL)
	{
		philos[i - 1]->r_fork_mutex = &philos[i]->l_fork_mutex;
		i++;
	}
	philos[i - 1]->r_fork_mutex = &philos[0]->l_fork_mutex;
}

t_philo	**create_philos(t_table *table)
{
	t_philo	**philos_arr;
	int	i;
	
	philos_arr = malloc(sizeof(t_philo *) * (table->data->num_philo + 1));
	if (!philos_arr)
	{
		printf("Failed malloc philos_arr\n");
		return (NULL);
	}
	philos_arr[table->data->num_philo] = NULL;
	i = 0;
	while(i < table->data->num_philo)
	{
		philos_arr[i] = create_philo(i, table);
		i++;
	}
	if (table->data->num_philo == 1)
		philos_arr[0]->r_fork_mutex = NULL;
	else
		init_right_forks(philos_arr);
	return (philos_arr);
}
