/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangin@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:20:55 by amalangi          #+#    #+#             */
/*   Updated: 2024/02/28 15:07:15 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	int				*dead;
	int				nb_of_eat_each_need;
	size_t			time_last_eat;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_start;

	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*protect_dead;
	pthread_mutex_t	*protect_eat;
	pthread_mutex_t	*protect_time;
}					t_philo;

typedef struct s_program
{
	int 			nb_philo;
	int				dead;
	int				nb_of_eat_each_need;
	pthread_mutex_t	protect_dead;
	pthread_mutex_t	protect_eat;
	pthread_mutex_t	protect_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_program;

long long int	ft_atoll(const char *str);
void			init_all(pthread_mutex_t *forks, t_philo *philos, t_program *program, char **argv);
void			create_thread(t_program	*program, t_philo *philo, pthread_mutex_t *forks);
size_t			ft_get_time(void);
int				ft_usleep(size_t milliseconds);
void			end_all_thread(t_program **program, t_philo **philo);
void			print_message(t_philo *philo, int message);

#endif