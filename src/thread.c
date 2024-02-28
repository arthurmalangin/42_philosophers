/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:07:39 by amalangi          #+#    #+#             */
/*   Updated: 2024/02/28 03:15:35 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->protect_dead);
	if (*(philo->dead_flag) == 1)
	{
		pthread_mutex_unlock(&philo->protect_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->protect_dead);
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->protect_time);
	printf("%ld %d has taken a fork\n", ft_get_time() - philo->time_start, philo->id);
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n", ft_get_time() - philo->time_start, philo->id);
	pthread_mutex_lock(&philo->protect_eat);
	printf("%ld %d is eating\n", ft_get_time() - philo->time_start, philo->id);
	philo->time_last_eat = ft_get_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->protect_eat);
	pthread_mutex_unlock(&philo->protect_time);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	think(t_philo *philo)
{
	//todo Data race do a mutex for time
	printf("%ld %d is thinking\n", ft_get_time() - philo->time_start, philo->id);
}

void	bed(t_philo *philo)
{
	printf("%ld %d is sleeping\n", ft_get_time() - philo->time_start, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	*routine(void *ptr)
{
	t_philo *philo;
	
	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (is_alive(philo) && philo->nb_philo > 1)
	{
		eat(philo);
		bed(philo);
		think(philo);
	}	
}

int	check_death(t_program **program, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*program)->nb_philo)
	{
		//printf("check death\n");
		pthread_mutex_lock(&(*philo)[i].protect_eat);//&program->philos[i].protect_eat
		if (ft_get_time() - (*program)->philos[i].time_last_eat >= (*program)->philos[i].time_to_die && (*program)->philos[i].dead == 0)
		{
			pthread_mutex_lock(&(*program)->philos[i].protect_dead);
			printf("%ld %d died\n", ft_get_time() - (*program)->philos->time_start, (*program)->philos[i].id);
			(*program)->philos[i].dead = 1;
			(*program)->dead = 1;
			pthread_mutex_unlock(&(*program)->philos[i].protect_dead);
			pthread_mutex_unlock(&(*program)->philos[i].protect_eat);
			return (1);
		}
		pthread_mutex_unlock(&(*program)->philos[i].protect_eat);
		i++;
	}
	return (0);
}

void	*monitoring(void *ptr)
{
	t_program *program;
	int	i;
	
	program = (t_program *)ptr;
	while (1)
	{
		if (check_death(&program, &program->philos) == 1)
			break ;
	}
	/*printf("dead flag %d\n", program->dead);
	printf("philo dead %d\n", program->philos[0].dead);
	printf("end monitoring\n");*/
	return (ptr);
}

void	create_thread(t_program	*program, t_philo *philo, pthread_mutex_t *forks)
{
	pthread_t elmonitor;
	int	i;

	i = 0;
	if (pthread_create(&elmonitor, NULL, &monitoring, program))
		printf("Error Thread creation\n");
	while (i < program->nb_philo)
	{
		if(pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			printf("Error Thread Creation\n");
		i++;
	}
	i = 0;
	while (i < program->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			printf("Error Thread join\n");
		i++;
	}
	if (pthread_join(elmonitor, NULL))
		printf("Error thread join\n");
}
