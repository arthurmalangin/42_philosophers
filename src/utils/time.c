/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:35:55 by amalangi          #+#    #+#             */
/*   Updated: 2024/01/30 19:38:54 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int     ft_usleep(size_t milliseconds)
{
        size_t  start;

        start = ft_get_time();
        while ((ft_get_time() - start) < milliseconds)
                usleep(500);
        return (0);
}

size_t  ft_get_time(void)
{
        struct timeval  time;

		gettimeofday(&time, NULL);
        return (time.tv_sec * 1000 + time.tv_usec / 1000);
}