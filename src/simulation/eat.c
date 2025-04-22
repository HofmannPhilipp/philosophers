/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 09:44:46 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, t_table *table, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	long	start_time;

	pthread_mutex_lock(fork1);
	start_time = get_long(&table->table_mutex, &table->start_time);
	print_status(philo, get_elapsed_time(start_time), FORK);
	pthread_mutex_lock(fork2);
	start_time = get_long(&table->table_mutex, &table->start_time);
	print_status(philo, get_elapsed_time(start_time), FORK);
}

static void	unlock_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_forks(philo, philo->table, &philo->l_fork_mutex,
			philo->r_fork_mutex);
	else
	{
		usleep(500);
		lock_forks(philo, philo->table, philo->r_fork_mutex,
			&philo->l_fork_mutex);
	}
	return (0);
}

void	eating(t_philo *philo, t_table *table)
{
	long	start_time;

	take_forks(philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	philo->meals_eaten++;
	start_time = get_long(&table->table_mutex, &table->start_time);
	print_status(philo, get_elapsed_time(start_time), EAT);
	usleep_plus(table->data->eat_time, table);
	if (is_full(philo, table))
		set_bool(&philo->philo_mutex, &philo->full, true);
	unlock_forks(&philo->l_fork_mutex, philo->r_fork_mutex);
}
