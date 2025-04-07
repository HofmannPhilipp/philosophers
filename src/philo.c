/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:05:21 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/07 18:03:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->bday = get_bday();
	philo->last_meal_time = get_bday();
	pthread_mutex_lock(&philo->table->print_mutex);
	pthread_mutex_unlock(&philo->table->print_mutex);
	while (philo->meals_eaten < philo->table->num_meals && get_curr_time(philo->last_meal_time) < philo->table->die_time)
	{
		thinking(philo);
		pthread_mutex_lock(&philo->table->waiter_mutex);
		pthread_mutex_lock(&philo->l_fork_mutex);
		pthread_mutex_lock(philo->r_fork_mutex);
		pthread_mutex_unlock(&philo->table->waiter_mutex);
		eating(philo);
		pthread_mutex_unlock(&philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
		sleeping(philo);
	}
	if (philo->meals_eaten < philo->table->num_meals)
	{
		print_msg(philo->id, get_curr_time(philo->bday), DEAD);
		exit(EXIT_FAILURE);
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
