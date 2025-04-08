/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:26 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	long	eat_time;
	
	if (philo->id % 2 == 0) {
		pthread_mutex_lock(&philo->l_fork_mutex);
		print_msg(philo, get_curr_time(philo->start_time), FORK);
		pthread_mutex_lock(philo->r_fork_mutex);
		print_msg(philo, get_curr_time(philo->start_time), FORK);
	} else {
		usleep(1000);
		pthread_mutex_lock(philo->r_fork_mutex);
		print_msg(philo, get_curr_time(philo->start_time), FORK);
		pthread_mutex_lock(&philo->l_fork_mutex);
		print_msg(philo, get_curr_time(philo->start_time), FORK);
	}
	eat_time = get_curr_time(philo->start_time);
	print_msg(philo, eat_time, EAT);
	philo->last_meal_time = get_start_time();
	usleep(philo->table->eat_time * 1000);
	unlock_forks(philo);
	philo->meals_eaten++;
}