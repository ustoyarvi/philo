#include "philo.h"

void    take_forks(t_philo *philo)
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

void    *eat(t_philo *philo)
{
    if (is_game_over(philo))
        return "game over";
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

void    sleep_philosopher(t_philo *philo)
{
    log_action(philo, "is sleeping");
    //usleep(philo->data->time_to_sleep * 1000);
    precise_sleep(philo->data->time_to_sleep * 1000, philo->data);
}

void    think(t_philo *philo)
{
    log_action(philo, "is thinking");
    precise_sleep(2000, philo->data);
}

void    *philosopher_routine(void *arg)
{
    t_philo *philo;
    bool    ready;

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

    if (philo->id % 2 == 0) // || philo->id == philo->data->num_philos)
        //precise_sleep(1000, philo->data);
        usleep(8000);
    while (1)
    {
        if (is_game_over(philo))
            break;
        if (eat(philo) != NULL)
            break;
        if (is_game_over(philo))
            break;
        sleep_philosopher(philo);
        if (is_game_over(philo))
            break;
        think(philo);
    }
    return (NULL);
}

int is_game_over(t_philo *philo)
{
    int game_over;

    pthread_mutex_lock(&philo->data->game_over_lock);
    game_over = philo->data->game_over;
    pthread_mutex_unlock(&philo->data->game_over_lock);

    return game_over;
}

// int is_game_over(t_philo *philo)
// {
//     int i;

//     i = 0;
//     while (i < philo->data->num_philos)
//     {
//         pthread_mutex_lock(&philo->data->game_over_lock);
//         if (philo->data->game_over)
//         {
//             pthread_mutex_unlock(&philo->data->game_over_lock);
//             return (1);
//         }
//         pthread_mutex_unlock(&philo->data->game_over_lock);
//         i++;
//     }
//     return (0);
// }

// int is_game_over(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->game_over_lock);
//     if (philo->data->game_over == 1)
//     {
//         pthread_mutex_unlock(&philo->data->game_over_lock);
//         return (1);
//     }
//     pthread_mutex_unlock(&philo->data->game_over_lock);
//     return (0);
// }