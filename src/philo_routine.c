/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsedlets < dsedlets@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:59:12 by dsedlets          #+#    #+#             */
/*   Updated: 2025/02/02 23:21:23 by dsedlets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id != philo->data->num_philos)
	{
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
	}
}

void	*eat(t_philo *philo)
{
	if (is_game_over(philo))
		return ("game over");
	take_forks(philo);
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	precise_sleep(philo->data->time_to_eat * 1000, philo->data);
	if (philo->id != philo->data->num_philos)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

void	sleep_philosopher(t_philo *philo)
{
	log_action(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep * 1000, philo->data);
}

void	think(t_philo *philo)
{
	log_action(philo, "is thinking");
	precise_sleep(2000, philo->data);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	ready;

	philo = (t_philo *)arg;
	ready = false;
	while (!ready)
	{
		pthread_mutex_lock(&philo->data->game_over_lock);
		ready = philo->data->all_threads_ready;
		pthread_mutex_unlock(&philo->data->game_over_lock);
		if (!ready)
			usleep(100);
	}
	if (philo->id % 2 == 0)
		usleep(8000);
	while (1)
	{
		if (is_game_over(philo))
			break ;
		if (eat(philo) != NULL)
			break ;
		if (is_game_over(philo))
			break ;
		sleep_philosopher(philo);
		if (is_game_over(philo))
			break ;
		think(philo);
	}
	return (NULL);
}
