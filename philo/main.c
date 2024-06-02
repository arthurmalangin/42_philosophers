/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:50:14 by amalangi          #+#    #+#             */
/*   Updated: 2024/06/01 17:58:35 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (ft_atoll(argv[1]) < 1)
	{
		printf("Error: Negative or null value for philosophers\n");
		return (1);
	}
	if (ft_atoll(argv[1]) > 200)
	{
		printf("Error: too many philosophers\n");
		return (1);
	}
	if (ft_atoll(argv[2]) < 60 || ft_atoll(argv[3])
		< 60 || ft_atoll(argv[4]) < 60)
	{
		printf("Error: values lower than 60 ms.\n");
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}

int	valid_digit_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && i <= 6)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: some inputs not digit !\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	t_program		program;

	if (valid_digit_input(argv))
		return (1);
	if (check_args(argc, argv))
		return (1);
	if (argc == 6)
	{
		if (ft_atoll(argv[5]) < 1 || ft_atoll(argv[5]) > 2147483647)
		{
			printf("Error: bad values for number_of_times_each_philosopher\n");
			return (1);
		}
	}
	if (ft_atoll(argv[2]) > 2147483647 || ft_atoll(argv[3])
		> 2147483647 || ft_atoll(argv[4]) > 2147483647)
	{
		printf("Error: values higher than INT_MAX ms.\n");
		return (1);
	}
	init_all(forks, philos, &program, argv);
	create_thread(&program, philos);
}
