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

    data->simulation_over = 0;
    data->start_time = get_time_in_ms();
    if (create_threads(data) != 0)
        return (1);
    if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
        return (1);
    if (join_threads(data) != 0)
        return (1);
    pthread_join(monitor_thread, NULL);
    return (0);
}