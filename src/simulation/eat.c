/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/23 19:09:20 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	print_status(philo, FORK);
	pthread_mutex_lock(fork2);
	print_status(philo, FORK);
}

static void	unlock_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_forks(philo, &philo->l_fork_mutex,
			philo->r_fork_mutex);
	else
	{
		lock_forks(philo, philo->r_fork_mutex,
			&philo->l_fork_mutex);
	}
}

static void	put_back_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		unlock_forks(&philo->l_fork_mutex,
			philo->r_fork_mutex);
	else
	{
		unlock_forks(philo->r_fork_mutex,
			&philo->l_fork_mutex);
	}
}

void	eating(t_philo *philo, t_table *table)
{
	long	eat_time;
	
	take_forks(philo);
	set_long(&philo->last_meal_time_mutex, &philo->last_meal_time, get_time());
	philo->meals_eaten++;
	print_status(philo, EAT);
	eat_time = get_long(&table->table_data_mutex, &table->data->eat_time);
	usleep_plus(eat_time, table);
	if (is_full(philo, table))
		set_bool(&philo->philo_full_mutex, &philo->full, true);
	put_back_forks(philo);
}
