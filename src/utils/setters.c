/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:05:32 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 08:40:45 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex,bool *ptr, bool new_value)
{
	pthread_mutex_lock(mutex);
	*ptr = new_value;
	pthread_mutex_unlock(mutex);
}

void	set_long(pthread_mutex_t *mutex, long *ptr, long new_value)
{
	pthread_mutex_lock(mutex);
	*ptr = new_value;
	pthread_mutex_unlock(mutex);
}
