/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:34:04 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/02 22:43:13 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
	{
		printf("Error: Failed to initialize data.\n");
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		printf("Error: Failed to start simulation.\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
