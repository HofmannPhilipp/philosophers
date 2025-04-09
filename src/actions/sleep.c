/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:23:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/09 16:05:11 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	long	sleep_time;
	
	sleep_time = get_curr_time(philo->start_time);
	print_msg(philo, sleep_time, SLEEP);
	usleep(philo->table->data->sleep_time * 1000);
}