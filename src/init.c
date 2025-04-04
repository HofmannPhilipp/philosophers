/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/04 11:04:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*create_table(int num_philo, int die_time, int eat_time, int sleep_time, int num_meals)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->num_philo = num_philo;
	table->die_time = die_time;
	table->eat_time = eat_time;
	table->sleep_time = sleep_time;
	table->num_meals = num_meals;
	pthread_mutex_init(&table->print_mutex, NULL);
	return (table);
}

t_philo	*create_philo(int id, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_init(&philo->mutex_fork, NULL);
	philo->id = id;
	philo->table = table;
	return (philo);
}

t_philo	**create_philos(int num_philo, int die_time, int eat_time, int sleep_time, int num_meals)
{
	t_philo	**philos_arr;
	t_table	*table;
	int	i;
	
	table = create_table(num_philo, die_time, eat_time, sleep_time, num_meals);
	philos_arr = malloc(sizeof(t_philo *) * (num_philo + 1));
	if (!philos_arr)
		hanlde_error("failed malloc philo_arr");
	philos_arr[num_philo] = NULL;
	i = 0;
	while(i < num_philo)
	{
		philos_arr[i] = create_philo(i + 1, table);
		i++;
	}
	return (philos_arr);
}