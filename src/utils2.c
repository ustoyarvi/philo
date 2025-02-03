/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:20:43 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/03 21:52:55 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
	precise_sleep(2000, philo->data);
}

void	log_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->game_over == 0)
		printf("%lld %d %s\n", get_time_in_ms() - philo->data->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	is_game_over(t_philo *philo)
{
	int	game_over;

	pthread_mutex_lock(&philo->data->game_over_lock);
	game_over = philo->data->game_over;
	pthread_mutex_unlock(&philo->data->game_over_lock);
	return (game_over);
}

int	printf_error_mutex(void)
{
	printf("Error: Mutex initialized failed\n");
	return (1);
}
