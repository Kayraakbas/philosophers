#include "philo.h"

bool ft_int_check(char *arg)
{
    int i;
    if (!arg)
        return false;
    i = 0;
    while (arg[i])
    {
        if (ft_isdigit(arg[i]) == false)
            return false;
        i++;
    }
    return true;
}

bool check_arguments(int ac, char **argv)
{
    int i = 1;
    //times are conted as miliseconds
    if (ac != 6)
    {
        printf("invalid arg count: you have entered %d arguments\n",ac);
        printf("example argument format: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
        return false;
    }
    while (argv[i])
    {
        printf("arg %d: %s\n", i, argv[i]);
        if (ft_int_check(argv[i]) == false)
        {
            printf("int check fault wrong arg: %d, %s\n",i, argv[i]);
            return false;
        }
        i++;
    }
    //convert the string to integer
    return true;
}
