/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isimulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:16:19 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/03 21:25:45 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, philosopher_routine,
				&(data->philos[i])) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	data->game_over = 0;
	data->all_threads_ready = 0;
	if (create_threads(data) != 0)
		return (1);
	data->start_time = get_time_in_ms();
	pthread_mutex_lock(&data->game_over_lock);
	data->all_threads_ready = 1;
	pthread_mutex_unlock(&data->game_over_lock);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (1);
	if (join_threads(data) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	return (0);
}
