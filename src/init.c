#include "philo.h"

int parse_arguments(int argc, char **argv, t_data *data)
{
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Error: Invalid number of arguments.\n");
        return (1);
    }
    i = 1;
    while (i < argc)
    {
        if (!is_positive_number(argv[i]))
        {
            printf("Error: All arguments must be positive number.\n");
            return (1);
        }
        i++;
    }
    if ((data->num_philos = ft_atoi(argv[1])) == 1)
    {
        printf("Sorry, one philosopher can't eat and so he died.\n");
        return (1);
    }
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->meals_required = (argc == 6) ? ft_atoi(argv[5]) : -1;
    if (data->num_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
    {
        printf("Error: Arguments must be greater than 0.\n");
        return (1);
    }
    return (0);
}

// Инициализация данных 
// 1. Выделение памяти для вилок и философов
int allocate_memory(t_data *data)
{
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
    {
        printf("Error: Memory allocation failed for forks.\n");
        return (1);
    }
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->num_philos)
    {
        printf("Error: Memory allocation failed for philosopher.\n");
        free(data->forks);
        return (1);
    }

/*    if (!data->forks || !data->philos)
        return (1); // Ошибка при выделении памяти 
*/
    return (0);
}

// 2. Инициализация мьютексов для вилок
int init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            printf("Error: Mutex initialized failed for fork %d.\n", i);
            return (1); // Ошибка при инициализации мьютекса
        }
        i++;
    }
    // Инициализируем мьютекс для вывода
  //  data->print_lock = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
    {
        printf("Error: Mutex initialized failed for print lock.\n");
        return (1);
    }
    // Инициализируем мьютекс для проверки статуса смерти
   // data->game_over_lock = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init(&data->game_over_lock, NULL) != 0)
    {
        printf("Error : Mutex initialized failed for simulation over lock.\n");
        return (1);
    }

    // Инициализируем мьютекс для блока времени ужина
    if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
    {
        printf("Error: Mutex initialization failed for meal_lock.\n");
        return (1);
    }
    return (0);
}

// 3. Настройка философов
void    setup_philosophers(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].last_meal = get_time_in_ms();
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        i++;
    }
}

int init_data(t_data *data)
{
    if (allocate_memory(data) != 0)
    {
        printf("Error: Failed to allocate memory.\n");
        return (1);
    }
    if (init_mutexes(data) != 0)
    {
        printf("Error: Failed to initialize mutexes.\n");
        free(data->forks);
        free(data->philos);
        return (1);
    }
    setup_philosophers(data);
    return (0);
}




