/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:58 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/23 19:13:36 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	long	total_threads;

	total_threads = get_long(&table->table_data_mutex, &table->data->num_philo) + 1;
	while ((get_long(&table->table_data_mutex, &table->num_threads_running) < total_threads))
			usleep(100);
}

bool	is_dead(t_philo *philo, t_table *table)
{
	long	last_meal_time;
	long	die_time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	last_meal_time = get_long(&philo->last_meal_time_mutex, &philo->last_meal_time);
	die_time = get_long(&table->table_data_mutex, &table->data->die_time);
	if (get_elapsed_time(last_meal_time) > die_time)
		return (true);
	return (false);
}

bool	is_full(t_philo *philo, t_table *table)
{
	long	num_meals;

	if (get_bool(&philo->philo_full_mutex, &philo->full))
		return (true);
	num_meals = get_long(&table->table_data_mutex, &table->data->num_meals);
	if (num_meals == NO_MEAL_LIMIT)
		return (false);
	if (philo->meals_eaten == num_meals)
		return (true);
	return (false);
}

void	usleep_plus(long duration, t_table *table)
{
	long	start;
	long	rem;

	start = get_time();
	while (get_elapsed_time(start) < duration)
	{
		if (is_simulation_finished(table))
			break ;
		rem = duration - get_elapsed_time(start);
		if (rem > 1000)
			usleep((rem / 2) * 1000);
		else
			while (get_elapsed_time(start) < duration)
				;
	}
}

void	one_philo(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	print_status(philo, FORK);
	pthread_mutex_unlock(&philo->l_fork_mutex);
	while (!is_simulation_finished(table))
		usleep(200);
}
void	set_start_time(t_table *table)
{
	int		i;
	t_philo	*philo;
	long	num_philo;

	num_philo = get_long(&table->table_data_mutex, &table->data->num_philo);
	i = 0;
	set_long(&table->start_time_mutex, &table->start_time, get_time());
	while (i < num_philo)
	{
		philo = table->philos[i];
		set_long(&philo->last_meal_time_mutex, &philo->last_meal_time, get_time());
		i++;
	}
	set_bool(&table->simulation_mutex, &table->simulation_start, true);
}