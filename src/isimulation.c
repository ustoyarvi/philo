#include "philo.h"

// Создание потоков для философов
int create_threads(t_data *data)
{
    int i;

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

// Ожидание завершения потоков
int join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}

int start_simulation(t_data *data)
{
    pthread_t   monitor_thread;
    int         i;

    data->game_over = 0;
    data->all_threads_ready = 0;

    if (create_threads(data) != 0)
        return (1);

    data->start_time = get_time_in_ms();
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