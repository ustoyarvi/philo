#include "philo.h"

void    take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
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

void    eat(t_philo *philo)
{
    take_forks(philo);
    log_action(philo, "is eating");
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->data->meal_lock);
    precise_sleep(philo->data->time_to_eat * 1000, philo->data);
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->data->meal_lock);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    sleep_philosopher(t_philo *philo)
{
    log_action(philo, "is sleeping");
    //usleep(philo->data->time_to_sleep * 1000);
    precise_sleep(philo->data->time_to_sleep * 1000, philo->data);
}

void    think(t_philo *philo)
{
    log_action(philo, "is thinking");
}

void    *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        precise_sleep(1000, philo->data);
        //usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&philo->data->simulation_over_lock);
        if (philo->data->simulation_over)
        {
            pthread_mutex_unlock(&philo->data->simulation_over_lock);
            break;
        }
        pthread_mutex_unlock(&philo->data->simulation_over_lock);
        eat(philo);
        sleep_philosopher(philo);
        think(philo);
    }
    return (NULL);
}