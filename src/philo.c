/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:05:21 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/08 14:07:41 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_start_time();
	philo->last_meal_time = get_start_time();
	while (philo->meals_eaten < philo->table->num_meals && !is_dead(philo))
	{
		thinking(philo);
		eating(philo);
		if (is_full(philo) || is_dead(philo))
			break;
		sleeping(philo);
	}
	return (NULL);
}

void	philo_loop(t_philo **philos)
{
	int	i;

	i = 0;
	while(philos[i] != NULL)
	{
		pthread_create(&philos[i]->thread, NULL, &routine, philos[i]);
		i++;
	}
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_mutex_destroy(&philos[i]->l_fork_mutex);
		i++;
	}
}
