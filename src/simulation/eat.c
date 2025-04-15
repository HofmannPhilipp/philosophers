/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:35:09 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (fork1)
	{
		pthread_mutex_lock(fork1);
		print_status(philo, get_elapsed_time(philo->start_time), FORK);
	}
	if(fork2)
	{
		pthread_mutex_lock(fork2);
		print_status(philo, get_elapsed_time(philo->start_time), FORK);
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
		// usleep(500);
		lock_forks(philo, philo->r_fork_mutex, &philo->l_fork_mutex);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	long	meals_eaten;
	
	take_forks(philo);
	if (philo->has_both_forks)
	{
		print_status(philo, get_elapsed_time(philo->start_time), EAT);
		set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
		usleep_plus(philo->table->data->eat_time, philo->table);
		meals_eaten = get_long(&philo->philo_mutex, &philo->meals_eaten);
		set_long(&philo->philo_mutex, &philo->meals_eaten, meals_eaten + 1);
	}
	unlock_forks(philo, &philo->l_fork_mutex, philo->r_fork_mutex);
	
}