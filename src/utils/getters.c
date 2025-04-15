/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:55:38 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 16:29:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool get_bool(pthread_mutex_t *mutex, bool *ptr)
{
	bool	value;
	pthread_mutex_lock(mutex);
	value = *ptr;
	pthread_mutex_unlock(mutex);
	return (value);
}

long	get_long(pthread_mutex_t *mutex, long *ptr)
{
	long	value;
	pthread_mutex_lock(mutex);
	value = *ptr;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	is_simulation_finished(t_table *table)
{
	bool	value;
	pthread_mutex_lock(&table->table_mutex);
	value = table->simulation_finished;
	pthread_mutex_unlock(&table->table_mutex);
	return (value);
}