#include "philo.h"

long long	ft_atoll(const char *str)
{
    int			i;
    long long	res;
    int			sign;

    sign = 1;
    res = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (ft_isdigit(str[i]))
    {
        res *= 10;
        res += str[i] - '0';
        i++;
    }
    return (res * sign);
}
