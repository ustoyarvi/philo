/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:49:51 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/02 22:58:15 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;
		pthread_mutex_lock(&data->meal_lock);
		while (i < data->num_philos)
		{
			if (get_time_in_ms()
				- data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", get_time_in_ms() - data->start_time,
					data->philos[i].id);
				pthread_mutex_lock(&data->game_over_lock);
				data->game_over = 1;
				pthread_mutex_unlock(&data->game_over_lock);
				pthread_mutex_unlock(&data->meal_lock);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			if (data->meals_required != -1
				&& data->philos[i].meals_eaten < data->meals_required)
				all_ate = 0;
			i++;
		}
		if (data->meals_required != -1 && all_ate)
		{
			pthread_mutex_lock(&data->print_lock);
			printf("All philosophers ate %d times\n", data->meals_required);
			pthread_mutex_lock(&data->game_over_lock);
			data->game_over = 1;
			pthread_mutex_unlock(&data->game_over_lock);
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_unlock(&data->print_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->meal_lock);
		usleep(500);
	}
	return (NULL);
}
