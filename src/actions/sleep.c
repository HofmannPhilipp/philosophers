/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:23:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/07 17:48:42 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	long	sleep_time;
	
	pthread_mutex_lock(&philo->table->print_mutex);
	sleep_time = get_curr_time(philo->bday);
	print_msg(philo->id + 1, sleep_time, SLEEP);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->sleep_time * 1000);
}