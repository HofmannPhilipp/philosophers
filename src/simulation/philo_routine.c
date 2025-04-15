/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:15:41 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:21:16 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



static void	thinking(t_philo *philo)
{
	print_status(philo, get_elapsed_time(philo->start_time), THINK);
}

static void	sleeping(t_philo *philo)
{
	print_status(philo, get_elapsed_time(philo->start_time), SLEEP);
	usleep_plus(philo->table->data->sleep_time, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->start_time, get_time());
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	while (!is_simulation_finished(philo->table) && !is_full(philo, philo->table) && !is_dead(philo, philo->table))
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
