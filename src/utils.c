#include "philo.h"

int is_positive_number(const char *str)
{
    int i;

    i = 0;
    if (!str || str[0] =='\0')
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_atoi(const char *str)
{
    int result;
    int i;

    result = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

// Получение текущего времени в миллисекундах
long long   get_time_in_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// и получение текущего времени в микросекундах
long long   get_time_in_mkrs(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void    precise_sleep(long usec, t_data *data)
{
    long long       start;
    long long       elapsed;
    long long       rem;

    start = get_time_in_mkrs();
    while (get_time_in_mkrs() - start < usec)
    {
        pthread_mutex_lock(&data->game_over_lock);
        if (data->game_over)
        {
            pthread_mutex_unlock(&data->game_over_lock);
            break;
        }
        pthread_mutex_unlock(&data->game_over_lock);
        elapsed = get_time_in_mkrs() - start;
        rem = usec - elapsed;
        if (rem > 1000)
            usleep(rem / 2);
        else
        {
            while (get_time_in_mkrs() - start < usec)
                ;
        }
   } 
}

void    log_action(t_philo *philo, char *action)
{
    // pthread_mutex_lock(&philo->data->game_over_lock);
    pthread_mutex_lock(&philo->data->print_lock);
    // printf("game_over = %d \n", philo->data->game_over);
    if (philo->data->game_over == 0)
        printf("%lld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_lock);
    // pthread_mutex_unlock(&philo->data->game_over_lock);
}   