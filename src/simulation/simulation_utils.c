/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:27:58 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:19:55 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	is_dead(t_philo *philo, t_table *table)
{
	long	last_meal_time;
	long	die_time;

	
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	die_time = get_long(&table->table_mutex, &table->data->die_time);
	if (get_elapsed_time(last_meal_time) < die_time)
		return (false);
	print_status(philo, get_elapsed_time(philo->start_time), DEAD);
	set_bool(&table->table_mutex, &table->is_dead, true);
	return (true);
}

bool	is_full(t_philo *philo, t_table *table)
{
	long	num_meals;
	long	meals_eaten;
	
	num_meals = get_long(&table->table_mutex, &table->data->num_meals);
	if (num_meals == INT_MIN)
		return (false);
	meals_eaten = get_long(&philo->philo_mutex, &philo->meals_eaten);
	if (meals_eaten == num_meals)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
		return (true);
	}
	return (false);
}

void	usleep_plus(long duration, t_table *table)
{
	long	start;
	long	rem;

	start = get_time();
	while(get_elapsed_time(start) < duration)
	{
		if (is_simulation_finished(table))
			break;
		rem = duration - get_elapsed_time(start);
		if (rem > 1000)
			usleep((rem / 2) * 1000);
		else
			while(get_elapsed_time(start) < duration)
				;
	}
}