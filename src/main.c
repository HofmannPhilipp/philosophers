/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/09 14:29:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	t_table	*table;
	
	if (argc < 5 || argc > 6)
	{
		print_usage_error();
		return (EXIT_FAILURE);
	}
	if (!parse_input(table, argv + 1))
		return (EXIT_FAILURE);
	philos = create_philos(table);
	philo_loop(philos);
	// pthread_mutex_destroy()
	return (EXIT_SUCCESS);
}