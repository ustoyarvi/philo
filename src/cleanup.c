#include "philo.h"

// Уничтожение мьютексов
void    cleanup(t_data *data)
{
    int i;
    // Уничтожаем мьютексы для вилок
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    // Уничтожаем мьютекс для вывода и мьютекс проверки статуса смерти
    pthread_mutex_destroy(&data->print_lock);
   // free(data->print_lock);
    pthread_mutex_destroy(&data->simulation_over_lock);
 //   free(data->simulation_over_lock);
    pthread_mutex_destroy(&data->meal_lock);

// Освобождаем память
    free(data->forks);
    free(data->philos);
}