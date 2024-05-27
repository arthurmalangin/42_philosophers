/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:35:55 by amalangi          #+#    #+#             */
/*   Updated: 2024/05/27 14:24:23 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timer_custom(size_t milliseconds)
{
	size_t	i;

	i = get_current_time();
	while ((get_current_time() - i) < milliseconds)
	{
		usleep(500);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	temptime;

	gettimeofday(&temptime, NULL);
	return (temptime.tv_sec * 1000 + temptime.tv_usec / 1000);
}
