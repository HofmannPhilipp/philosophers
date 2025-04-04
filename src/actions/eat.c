/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:53 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/04 11:04:48 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	philo->left_fork = &philo->mutex_fork;
	print_msg(philo->id, get_curr_time(philo->bday), FORK);
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_lock(&philo->right_fork);
	print_msg(philo->id, get_curr_time(philo->bday), FORK);
	pthread_mutex_unlock(&philo->right_fork);
	print_msg(philo->id, get_curr_time(philo->bday), EAT);
	usleep(philo->table->eat_time);
	philo->last_meal_time = get_curr_time(philo->bday);
}