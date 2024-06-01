/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:04:55 by amalangi          #+#    #+#             */
/*   Updated: 2024/06/01 16:35:00 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_all_thread(t_program **program, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*program)->nb_philo)
	{
		pthread_mutex_destroy((*philo)[i].protect_dead);
		pthread_mutex_destroy((*philo)[i].protect_eat);
		pthread_mutex_destroy((*philo)[i].protect_time);
		i++;
	}
	i = 0;
	while (i < (*program)->nb_philo)
	{
		pthread_mutex_destroy(&(*program)->forks[i]);
		i++;
	}
	i = 0;
	while (i < (*program)->nb_philo)
	{
		pthread_detach((*philo)[i].thread);
		i++;
	}
}
