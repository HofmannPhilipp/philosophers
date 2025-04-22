/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:06:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 13:52:52 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	validate_inputs(long num_philo, long die_time, long eat_time,
	long sleep_time)
{
	if (num_philo == INT_MIN || die_time == INT_MIN
		|| eat_time == INT_MIN || sleep_time == INT_MIN)
	{
		printf("Invalid (non-numeric or out-of-range) input\n");
		return (false);
	}
	if (num_philo < 1 || num_philo > 200)
	{
		printf("Invalid number of philosophers\n");
		return (false);
	}
	if (die_time < 60 || eat_time < 60 || sleep_time < 60)
	{
		printf("Time values must be at least 60ms\n");
		return (false);
	}
	if (die_time > INT_MAX || eat_time > INT_MAX || sleep_time > INT_MAX)
	{
		printf("Time values exceed INT_MAX\n");
		return (false);
	}
	return (true);
}

bool	parse_input(t_data *data, char *argv[])
{
	data->num_philo = ft_atol(argv[0]);
	data->die_time = ft_atol(argv[1]);
	data->eat_time = ft_atol(argv[2]);
	data->sleep_time = ft_atol(argv[3]);
	if (!validate_inputs(data->num_philo, data->die_time, data->eat_time,
			data->sleep_time))
		return (false);
	if (argv[4])
	{
		data->num_meals = ft_atol(argv[4]);
		if ((data->num_meals < 1 || data->num_meals > INT_MAX))
		{
			printf("Invalid number of meals\n");
			return (false);
		}
	}
	else
		data->num_meals = NO_MEAL_LIMIT;
	return (true);
}
