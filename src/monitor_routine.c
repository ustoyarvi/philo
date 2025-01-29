#include "philo.h"

void    *monitor_routine(void *arg)     // Мониторинг состояния философов (не умер ли кто-то)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->meal_lock);
            if (get_time_in_ms() - data->philos[i].last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_lock);
         //       printf("get_time_in_ms = %lld \n", get_time_in_ms());
         //       printf("data->philos[%d].last_meal = %lld \n", i, data->philos[i].last_meal);
         //       printf("%lld - %lld = %lld \n", get_time_in_ms(), data->philos[i].last_meal, (get_time_in_ms() - data->philos[i].last_meal));
        //      printf("Время без еды %lld БОЛЬШЕ > ЧЕМ  %lld ? у философа номер %d\n",  (get_time_in_ms() - data->philos[i].last_meal), data->time_to_die, i + 1);
                printf("%lld %d died\n", get_time_in_ms() - data->start_time,
                     data->philos[i].id);
                pthread_mutex_unlock(&data->print_lock);
                pthread_mutex_lock(&data->simulation_over_lock);
                data->simulation_over = 1;
                pthread_mutex_unlock(&data->simulation_over_lock);
                pthread_mutex_unlock(&data->meal_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&data->meal_lock);
            i++;
        }
        precise_sleep(1000, data); 
        //usleep(1000); // задержка для оптимизации
    }
    return (NULL);
}