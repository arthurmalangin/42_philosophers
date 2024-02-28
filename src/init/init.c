/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangin@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:06:52 by amalangi          #+#    #+#             */
/*   Updated: 2024/02/26 23:11:12 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void init_program(t_program *program, pthread_mutex_t *forks, char **argv)
{
	program->dead = 0;
	program->nb_philo = (int)ft_atoll(argv[1]);
	if (argv[5])
		program->nb_of_eat_each_need = (int)ft_atoll(argv[5]);
	else
		program->nb_of_eat_each_need = -1;
	program->forks = forks;
	pthread_mutex_init(&program->protect_dead, NULL);
	pthread_mutex_init(&program->protect_eat, NULL);
}

void	init_forks(pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = (int)ft_atoll(argv[1]);
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	nb_philo;
	
	i = 0;
	nb_philo = (int)ft_atoll(argv[1]);
	while (i < nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_philo = nb_philo;
		philos[i].dead_flag = &program->dead;
		philos[i].dead = 0;
		philos[i].nb_of_eat_each_need = program->nb_of_eat_each_need;
		pthread_mutex_init(&philos[i].protect_dead, NULL);
		pthread_mutex_init(&philos[i].protect_eat, NULL);
		pthread_mutex_init(&philos[i].protect_time, NULL);
		if (i == 0)
		{
			philos[0].l_fork = &forks[nb_philo - 1];
			philos[0].r_fork = &forks[0];
		}
		else
		{
			philos[i].l_fork = &forks[i - 1];
			philos[i].r_fork = &forks[i];
		}
		philos[i].time_to_die = ft_atoll(argv[2]);
		philos[i].time_to_eat = ft_atoll(argv[3]);
		philos[i].time_to_sleep = ft_atoll(argv[4]);
		philos[i].time_last_eat = ft_get_time();
		philos[i].time_start = ft_get_time();
		i++;
	}
}

void	init_all(pthread_mutex_t *forks, t_philo *philos, t_program *program, char **argv)
{
	init_program(program, forks, argv);
	init_forks(forks, argv);
	init_philos(philos, program, forks, argv);
	program->philos = philos;
}