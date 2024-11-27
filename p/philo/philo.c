/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:51:04 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 16:50:16 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_mutex *params)
{
	int	i;

	i = 0;
	while (i < params->philos_num)
	{
		pthread_mutex_destroy(&params->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&params->print);
	pthread_mutex_destroy(&params->death);
}

void	start(t_mutex *params)
{
	t_philo		philos[200];
	pthread_t	th[200];
	int			i;

	i = 0;
	params -> start = get_time();
	pthread_mutex_init(&params->print, NULL);
	pthread_mutex_init(&params->death, NULL);
	while (i < params -> philos_num)
	{
		philos[i].id = i + 1;
		philos[i].init = params;
		philos[i].last_meal = get_time();
		philos[i].meals_num = 0;
		philos[i].left_fork = &params -> fork[i];
		philos[i].right_fork = &params -> fork[(i + 1) % params -> philos_num];
		i++;
	}
	init_meals(params, philos);
	create_philos(params, philos, th);
	monitor_death(philos);
	join_philos(th, params);
	destroy(params);
}

void	init(t_mutex *params)
{
	int	i;

	i = 0;
	while (i < params->philos_num)
	{
		if (pthread_mutex_init(&params->fork[i], NULL) != 0)
			return ;
		i++;
	}
}

int	initialize(char **av, int ac)
{
	t_mutex	params;

	params.philos_num = ft_atoi(av[1]);
	params.time_to_die = ft_atoi(av[2]);
	params.time_to_eat = ft_atoi(av[3]);
	params.time_to_sleep = ft_atoi(av[4]);
	params.dead = 0;
	if (ac == 6)
		params.must_eat = ft_atoi(av[5]);
	else
		params.must_eat = -1;
	if (params.must_eat == 0)
		return (0);
	init(&params);
	start(&params);
	if (params.dead)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error\n");
		return (1);
	}
	if (parse(av, ac))
	{
		printf("Error\n");
		return (1);
	}
	if (initialize(av, ac))
		return (1);
	return (0);
}
