/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:12:51 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/03 21:12:54 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_number(argv[i]))
		{
			printf("Error: All arguments must be positive number.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_data_values(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos == 1)
	{
		printf("Sorry, one philosopher can't eat and so he died.\n");
		return (1);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: Arguments must be greater than 0.\n");
		return (1);
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (validate_arguments(argc, argv) != 0)
		return (1);
	if (set_data_values(argc, argv, data) != 0)
		return (1);
	return (0);
}
