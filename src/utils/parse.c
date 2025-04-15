/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:06:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/15 15:11:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_inputs(long num_philo, long die_time, long eat_time, long sleep_time, long num_meals)
{
	if (num_philo == INT_MIN || die_time == INT_MIN ||
		eat_time == INT_MIN || sleep_time == INT_MIN)
	{
		printf("Invalid (non-numeric or out-of-range) input\n");
		return (1);
	}if (num_philo < 1 || num_philo > 200)
	{
		printf("Invalid number of philosophers\n");
		return (1);
	}
	if (die_time > INT_MAX || die_time < 60 ||
		eat_time > INT_MAX || eat_time < 60 ||
		sleep_time > INT_MAX || sleep_time < 60)
	{
		printf("Time values must be between 60 and INT_MAX\n");
		return (1);
	}
	if (num_meals == INT_MIN || num_meals < 1 || num_meals > INT_MAX)
		{
			printf("Invalid number of meals\n");
			return (1);
		}
	return (0);
}
int	parse_input(t_data *data, char *argv[])
{
	long	num_philo;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	num_meals;
	
	num_philo = ft_atol(argv[0]);
	die_time = ft_atol(argv[1]);
	eat_time = ft_atol(argv[2]);
	sleep_time = ft_atol(argv[3]);
	if (argv[4])
	{
		num_meals = ft_atol(argv[4]);
		if (valid_inputs(num_philo, die_time, eat_time, sleep_time, num_meals) != 0)
			return (1);
 	}
	else
		data->num_meals = INT_MIN;
	data->num_philo = (int)num_philo;
	data->die_time = (int)die_time;
	data->eat_time = (int)eat_time;
	data->sleep_time = (int)sleep_time;
	return (0);
}
