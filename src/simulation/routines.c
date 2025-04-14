/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/14 11:02:24 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	philo->start_time = get_time();
	philo->last_meal_time = get_time();
	while ((philo->meals_eaten < philo->table->data->num_meals) && !is_dead(philo))
	{
		thinking(philo);
		eating(philo);
		if (is_full(philo) || is_dead(philo))
			break;
		sleeping(philo);
	}
	return (NULL);
}