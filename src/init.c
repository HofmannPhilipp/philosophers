/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/08 13:31:53 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_table(int num_philo, int die_time, int eat_time, int sleep_time, int num_meals)
{
	t_table			*table;

	table = malloc(sizeof(t_table));
	table->num_philo = num_philo;
	table->die_time = die_time;
	table->eat_time = eat_time;
	table->sleep_time = sleep_time;
	table->num_meals = num_meals;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->dead_mutex, NULL);
	return (table);
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

t_philo	**create_philos(t_table *table)
{
	t_philo	**philos_arr;
	int	i;
	
	philos_arr = malloc(sizeof(t_philo *) * (table->num_philo + 1));
	if (!philos_arr)
		hanlde_error("failed malloc philo_arr");
	philos_arr[table->num_philo] = NULL;
	i = 0;
	while(i < table->num_philo)
	{
		philos_arr[i] = create_philo(i, table);
		i++;
	}
	init_right_forks(philos_arr);
	return (philos_arr);
}

void	init_right_forks(t_philo **philos)
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