/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:04:55 by amalangi          #+#    #+#             */
/*   Updated: 2024/01/31 15:47:37 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_all_thread(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < program->nb_philo - 1)
	{
		pthread_mutex_destroy(&philo[i].protect_dead);
		pthread_mutex_destroy(&philo[i].protect_eat);
		i++;
	}
	i = 0;
	while (i < program->nb_philo - 1)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
}