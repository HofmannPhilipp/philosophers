/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/14 11:01:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (fork1)
	{
		pthread_mutex_lock(fork1);
		print_msg(philo, get_elapsed_time(philo->start_time), FORK);
	}
	if(fork2)
	{
		pthread_mutex_lock(fork2);
		print_msg(philo, get_elapsed_time(philo->start_time), FORK);
	}
	if (fork1 && fork2)
		philo->has_both_forks = true;
}

static void	unlock_forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (fork1)
		pthread_mutex_unlock(fork1);
	if(fork2)
		pthread_mutex_unlock(fork2);
	philo->has_both_forks = false;
}


static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_forks(philo, &philo->l_fork_mutex, philo->r_fork_mutex);
	else
	{
		usleep(1000);
		lock_forks(philo, philo->r_fork_mutex, &philo->l_fork_mutex);
	}
	return (0);
}

void	eating(t_philo *philo)
{

	take_forks(philo);
	if (philo->has_both_forks)
	{
		print_msg(philo, get_elapsed_time(philo->start_time), EAT);
		philo->last_meal_time = get_time();
		usleep(philo->table->data->eat_time * 1000);
		philo->meals_eaten++;
	}
	unlock_forks(philo, &philo->l_fork_mutex, philo->r_fork_mutex);
}