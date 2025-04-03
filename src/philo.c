/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:05:21 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/03 13:43:04 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		meals_eaten;

	philo = (t_philo *)arg;
	meals_eaten = 0;
	philo->bday = get_bday();
	while (meals_eaten < philo->table->num_meals && get_curr_time(philo->bday) < philo->table->die_time);
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->mutex);
			
		}
		if (philo->has_fork)
		{
			usleep(philo->table->eat_time);
			philo->bday = get_bday();
			meals_eaten ++;
			usleep(philo->table->sleep_time);
		}
	}
	if (meals_eaten < philo->table->num_meals)
		print_msg(philo->id, get_curr_time(philo->bday), DEAD);
	// printf("id: %d fork: %p\n", philo->id, &philo->mutex);
	// if (philo->id % 2 == 0)
	// {
	// 	print_msg(philo->id, get_curr_time() - philo->bday, FORK);
	// }
	
	return (NULL);
}

void	philo_loop(t_philo **philos)
{
	pthread_t	waiter;
	int	i;

	i = 0;
	// print_arr(philos);
	pthread_create(&monitor,NULL, &monitor, philos[i]);
	
	while(philos[i] != NULL)
	{
		// printf("%d\n", i);
		pthread_create(&philos[i]->thread, NULL, &routine, philos[i]);
		i++;
	}
	i = 0;
	while (philos[i] != NULL)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
}
