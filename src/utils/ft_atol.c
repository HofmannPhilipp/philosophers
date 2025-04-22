/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:12:28 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/22 11:05:43 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

static int	ft_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	sum;

	sign = 1;
	while (ft_iswhitespace(*str) && *str)
		str ++;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		str ++;
	}
	sum = 0;
	while (ft_isdigit(*str))
	{
		sum = sum * 10 + (*str - '0');
		str ++;
	}
	if (*str != '\0')
		return (INT_MIN);
	return (sign * sum);
}
