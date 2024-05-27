/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:07:39 by amalangi          #+#    #+#             */
/*   Updated: 2024/05/27 14:50:28 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->protect_dead);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->protect_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->protect_dead);
	return (0);
}

void	message_secure(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->protect_dead);
	if (*philo->dead == 0)
	{
		pthread_mutex_lock(philo->protect_message);
		printf("\x1B[36m[%zu]\033[0m \x1B[35m%d\033[0m %s\n",
			get_current_time() - philo->time_start, philo->id, message);
		pthread_mutex_unlock(philo->protect_message);
	}
	pthread_mutex_unlock(philo->protect_dead);
}

void	create_thread(t_program	*program,
t_philo *philo)
{
	pthread_t	elmonitor;
	int			i;

	i = 0;
	if (pthread_create(&elmonitor, NULL, &monitoring, program))
		printf("Error Thread creation\n");
	while (i < program->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			printf("Error Thread Creation\n");
		i++;
	}
	i = 0;
	if (pthread_join(elmonitor, NULL))
		printf("Error thread join\n");
	while (i < program->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			printf("Error Thread join\n");
		i++;
	}
}
