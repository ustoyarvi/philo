#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

 //   // Подавляем предупреждения, если временно не используем параметры
 //   (void)argc;
 //   (void)argv;

    if (parse_arguments(argc, argv, &data) != 0)
        return (1);
    printf("Parsed arguments successfully!\n");
    printf("Number of philosophers: %d\n", data.num_philos);
    printf("Time to die: %lld\n", data.time_to_die);
    printf("Time to eat: %lld\n", data.time_to_eat);
    printf("Time to sleep: %lld\n", data.time_to_sleep);
    printf("Meals required: %d\n", data.meals_required);
    if (init_data(&data) != 0)
    {
        printf("Error: Failed to initialize data.\n");
        return (1);
    }
    if (start_simulation(&data) != 0)
    {
        printf("Error: Failed to start simulation.\n");
        cleanup(&data);
        return (1);
    }
    cleanup(&data);
    return (0);
}