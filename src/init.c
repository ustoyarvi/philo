/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:21:34 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/03 23:03:45 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_memory(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("Error: Memory allocation failed for forks.\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->num_philos)
	{
		printf("Error: Memory allocation failed for philosopher.\n");
		free(data->forks);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			printf_error_mutex();
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		printf_error_mutex();
	if (pthread_mutex_init(&data->game_over_lock, NULL) != 0)
		printf_error_mutex();
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		printf_error_mutex();
	return (0);
}

void	setup_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data)
{
	if (allocate_memory(data) != 0)
	{
		printf("Error: Failed to allocate memory.\n");
		return (1);
	}
	if (init_mutexes(data) != 0)
	{
		printf("Error: Failed to initialize mutexes.\n");
		free(data->forks);
		free(data->philos);
		return (1);
	}
	setup_philosophers(data);
	return (0);
}

void	init_last_meal_times(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		pthread_mutex_lock(&data->print_lock);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
}
