/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:10:03 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/07 17:29:31 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	print_msg(philo->id + 1, get_curr_time(philo->bday), THINK);
	pthread_mutex_unlock(&philo->table->print_mutex);
}