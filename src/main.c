/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/03 13:09:09 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	
	if (argc < 5 || argc > 6)
	{
		print_usage_error();
		return (EXIT_FAILURE);
	}
	philos = create_philos(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]), ft_atoi(argv[5]));
	philo_loop(philos);
	// pthread_mutex_destroy()
	return (EXIT_SUCCESS);
}