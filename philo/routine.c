/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:09:31 by amalangi          #+#    #+#             */
/*   Updated: 2024/05/27 14:36:06 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		message_secure(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		message_secure(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		message_secure(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		message_secure(philo, "has taken a fork");
	}
	philo->is_eating = 1;
	message_secure(philo, "is eating");
	pthread_mutex_lock(philo->protect_eat);
	philo->time_last_eat = get_current_time();
	philo->nb_eat++;
	pthread_mutex_unlock(philo->protect_eat);
	timer_custom(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	message_secure(philo, "is thinking");
}

void	bed(t_philo *philo)
{
	message_secure(philo, "is sleeping");
	timer_custom(philo->time_to_sleep);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		timer_custom(1);
	while (!is_alive(philo) && philo->nb_philo > 1)
	{
		eat(philo);
		bed(philo);
		think(philo);
	}
	return (ptr);
}
