/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:37 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 21:09:35 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_must_eat(t_philo *philo)
{
	int	i;

	if (philo->init->must_eat == -1)
		return (0);
	i = 0;
	while (i < philo->init->philos_num)
	{
		pthread_mutex_lock(&philo[i].meals_nums);
		if (philo[i].meals_num < philo->init->must_eat)
		{
			pthread_mutex_unlock(&philo[i].meals_nums);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meals_nums);
		i++;
	}
	pthread_mutex_lock(&philo->init->death);
	philo->init->dead = 1;
	pthread_mutex_unlock(&philo->init->death);
	return (1);
}

int	monitor_death(t_philo *philo)
{
	while (1)
	{
		if (check_philos_death(philo))
			return (1);
		if (check_must_eat(philo))
			return (1);
	}
}

void	init_meals(t_mutex *params, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < params->philos_num)
	{
		if (pthread_mutex_init(&philo[i].meals_eating, NULL) != 0)
		{
			printf("Error\n");
			destroy(params);
			return ;
		}
		if (pthread_mutex_init(&philo[i].meals_nums, NULL) != 0)
		{
			printf("Error\n");
			destroy(params);
			return ;
		}
		i++;
	}
}

void	create_philos(t_mutex *params, t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < params -> philos_num)
	{
		if (pthread_create(&th[i], NULL, routine, &philo[i]) != 0)
		{
			printf("Error\n");
			destroy(params);
			return ;
		}
		i++;
	}
}

void	join_philos(pthread_t *th, t_mutex *params)
{
	int	i;

	i = 0;
	while (i < params -> philos_num)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			printf("Error\n");
			destroy(params);
			return ;
		}
		i++;
	}
}
