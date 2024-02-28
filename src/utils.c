/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 03:07:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/02/28 03:13:43 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_message(t_philo *philo, int message)
{
    pthread_mutex_lock(&philo->protect_dead);
    if (philo->dead != 0)
    {
        pthread_mutex_lock(&philo->protect_time);
        if (message == 1)
            printf("%ld %d has taken a fork\n", ft_get_time() - philo->time_start, philo->id);
        else if (message == 2)
            printf("%ld %d is eating\n", ft_get_time() - philo->time_start, philo->id);
        else if (message == 3)
            printf("%ld %d is sleeping\n", ft_get_time() - philo->time_start, philo->id);
        else if (message == 4)
            printf("%ld %d is thinking\n", ft_get_time() - philo->time_start, philo->id);
        else if (message == 5)
            printf("%ld %d died\n", ft_get_time() - philo->time_start, philo->id);
        pthread_mutex_unlock(&philo->protect_time);
    }
    pthread_mutex_unlock(&philo->protect_dead);
}