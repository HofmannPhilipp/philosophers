/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:50:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/04/09 16:16:19 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	t_table	table;
	t_data	data;
	
	philos = NULL;
	if (argc < 5 || argc > 6)
	{
		print_usage_error();
		return (EXIT_FAILURE);
	}
	if (parse_input(&data, argv + 1) != 0)
		return (EXIT_FAILURE);
	if (init_table(&table, &data) != 0)
		return (EXIT_FAILURE);
	philos = create_philos(&table);
	if (!philos)
		return (EXIT_FAILURE);
	philo_loop(philos);
	return (EXIT_SUCCESS);
}
