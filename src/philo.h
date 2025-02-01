#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

// Структура для представления философа
typedef struct s_philo
{
    int             id;          // Идентификатор философа
    pthread_t       thread;     // Поток, в котором работает философ
    pthread_mutex_t *left_fork;     // Указатель на левую вилку
    pthread_mutex_t *right_fork;    // Указатель на правую вилку
    long long       last_meal;      // Время последнего приема пищи
    int             meals_eaten;    // Количество съеденных приёмов пищи
    struct s_data   *data; // Указатель на общие данные
}            t_philo;

// Структура для представления общих данных симуляции
typedef struct s_data
{
    int             num_philos;     // Количество философов
    long long       time_to_die;    // Время до смерти от голода
    long long       time_to_eat;    // Время на прием пищи
    long long       time_to_sleep;  // Время на сон
    int             meals_required; // Максимальное количество приемов пищи, которое должен съесть каждый философ
    long long       start_time;     // Время начала симуляции (используется для расчета времени)
    int             game_over; // Флаг завершения
    int             all_threads_ready; // Флаг готовности всех потоков
    pthread_mutex_t *forks;     // теперь это снова НЕ Массив указателей ( * Указатель на массив мьютексов для вилок)
    pthread_mutex_t print_lock;    // Мьютекс для синхронизации вывода сообщений в консоль
    pthread_mutex_t game_over_lock; // Мьютекс для лока при проверке статуса смерти 
    pthread_mutex_t meal_lock; // Мьютекс для синхронизации доступа к времени последнего приёма пищи
    t_philo         *philos;    // Указатель на массив философов
}            t_data;

// Вспомогательные функции
int         is_positive_number(const char *str);
int         ft_atoi(const char *str);
int         is_game_over(t_philo *philo);
long long   get_time_in_ms(void); // Функция для получения текущего времени
long long   get_time_in_mkrs(void); // Функция для получения текущего времени в микросекундах
void        precise_sleep(long usec, t_data *data);



// Парсинг и инициализация
int         parse_arguments(int argc, char **argv, t_data *data);
int         init_data(t_data *data);

// Симуляция
int         start_simulation(t_data *data);
void        *philosopher_routine(void *arg);
void        *monitor_routine(void *arg);

// Логика философа
void        take_forks(t_philo *philo);
void        *eat(t_philo *philo);
void        sleep_philosopher(t_philo *philo);
void        think(t_philo *philo);

// Логирование и очистка
void        log_action(t_philo *philo, char *action);
void        cleanup(t_data *data);


#endif