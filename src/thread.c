/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deymons <deymons@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:07:39 by amalangi          #+#    #+#             */
/*   Updated: 2024/03/04 11:59:56 by deymons          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->protect_dead);
	//printf("philo %d: dead flag %d\n", philo->id, *philo->dead);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->protect_dead);
		return (0);
	}
	pthread_mutex_unlock(philo->protect_dead);
	return (1);
}

void message_secure(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->protect_dead);
	if (*philo->dead == 0)
		printf("%ld %d %s\n", ft_get_time() - philo->time_start, philo->id, message);
	//else
	//	printf("%ld %d %s dead state: %d\n", ft_get_time() - philo->time_start, philo->id, "is dead", *philo->dead);
	pthread_mutex_unlock(philo->protect_dead);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	message_secure(philo, "has taken a fork");
	//printf("%ld %d has taken a fork\n", ft_get_time() - philo->time_start, philo->id);
	pthread_mutex_lock(philo->r_fork);
	message_secure(philo, "has taken a fork");
	//printf("%ld %d has taken a fork\n", ft_get_time() - philo->time_start, philo->id);
	pthread_mutex_lock(philo->protect_eat);
	message_secure(philo, "is eating");
	//printf("%ld %d is eating\n", ft_get_time() - philo->time_start, philo->id);
	philo->time_last_eat = ft_get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(philo->protect_eat);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	think(t_philo *philo)
{
	//todo Data race do a mutex for time
	message_secure(philo, "is thinking");
	//printf("%ld %d is thinking\n", ft_get_time() - philo->time_start, philo->id);
}

void	bed(t_philo *philo)
{
	//printf("%ld %d is sleeping\n", ft_get_time() - philo->time_start, philo->id);
	message_secure(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	*routine(void *ptr)
{
	t_philo *philo;
	
	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	//printf("philo %d is alive and death status is: %d\n", philo->id, *philo->dead);
	while (is_alive(philo) && philo->nb_philo > 1)
	{
		eat(philo);
		bed(philo);
		think(philo);
	}
	return (ptr);
}

int	check_death(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		pthread_mutex_lock(&program->protect_eat);
		if (ft_get_time() - program->philos[i].time_last_eat >= program->philos[i].time_to_die)
		{
			pthread_mutex_lock(&program->protect_dead);
			printf("%ld %d died\n", ft_get_time() - program->philos->time_start, program->philos[i].id);
			*philo->dead = 1;
			pthread_mutex_unlock(&program->protect_dead);
			pthread_mutex_unlock(&program->protect_eat);
			return (1);
		}
		pthread_mutex_unlock(&program->protect_eat);
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
	t_program *program;
	int	i;
	
	program = (t_program *)ptr;
	while (1)
	{
		if (check_death(program, program->philos) == 1)
			break ;
		if (check_each_eat(program) == 1)
		{
			printf("All philo have eaten enough\n");
			pthread_mutex_lock(&program->protect_dead);
			program->dead = 1;
			pthread_mutex_unlock(&program->protect_dead);
			break ;
		}
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
	if (pthread_join(elmonitor, NULL))
		printf("Error thread join\n");
	while (i < program->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			printf("Error Thread join\n");
		i++;
	}
}
