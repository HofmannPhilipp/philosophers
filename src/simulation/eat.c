/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/25 13:48:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		print_status(philo, FORK);
		pthread_mutex_lock(philo->r_fork_mutex);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork_mutex);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->l_fork_mutex);
		print_status(philo, FORK);
	}
}

static void	put_back_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork_mutex);
	pthread_mutex_unlock(philo->r_fork_mutex);
}

void	eating(t_philo *philo, t_table *table)
{
	long	eat_time;

	take_forks(philo);
	set_long(&philo->last_meal_time_mutex, &philo->last_meal_time, get_time());
	philo->meals_eaten++;
	print_status(philo, EAT);
	eat_time = get_long(&table->table_data_mutex, &table->data->eat_time);
	usleep_plus(eat_time);
	if (is_full(philo, table))
		set_bool(&philo->philo_full_mutex, &philo->full, true);
	put_back_forks(philo);
}
