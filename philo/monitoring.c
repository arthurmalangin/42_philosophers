/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:12:30 by amalangi          #+#    #+#             */
/*   Updated: 2024/05/27 14:24:10 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		if (philosopher_dead(&philo[i], philo[i].time_to_die))
		{
			message_secure(philo, "\033[31mis diead\033[0m");
			pthread_mutex_lock(philo[i].protect_dead);
			*(philo[i].dead) = 1;
			pthread_mutex_unlock(philo[i].protect_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_each_eat(t_program *program)
{
	int	i;

	i = 0;
	if (program->nb_of_eat_each_need == -1)
		return (0);
	while (i < program->nb_philo)
	{
		pthread_mutex_lock(&program->protect_eat);
		if (program->philos[i].nb_eat < program->nb_of_eat_each_need)
		{
			pthread_mutex_unlock(&program->protect_eat);
			return (0);
		}
		pthread_mutex_unlock(&program->protect_eat);
		i++;
	}
	return (1);
}

void	*monitoring(void *ptr)
{
	t_program	*program;

	program = (t_program *)ptr;
	while (1)
	{
		if (check_death(program, program->philos) == 1)
			break ;
		if (check_each_eat(program) == 1)
		{
			pthread_mutex_lock(&program->protect_message);
			printf("\x1B[32mAll philo have eaten enough\033[0m\n");
			pthread_mutex_unlock(&program->protect_message);
			pthread_mutex_lock(&program->protect_dead);
			program->dead = 1;
			pthread_mutex_unlock(&program->protect_dead);
			break ;
		}
	}
	return (ptr);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->protect_eat);
	if (get_current_time() - philo->time_last_eat > time_to_die
		&& philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->protect_eat);
		return (1);
	}
	pthread_mutex_unlock(philo->protect_eat);
	return (0);
}
