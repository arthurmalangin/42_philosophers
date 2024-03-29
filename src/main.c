/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deymons <deymons@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:50:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/03/04 12:01:32 by deymons          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	t_program		program;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (ft_atoll(argv[1]) > 200)
	{
		printf("Error: too many philosophers\n");
		return (1);
	}
	init_all(forks, philos, &program, argv);
	create_thread(&program, philos, forks);
}