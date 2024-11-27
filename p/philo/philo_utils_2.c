/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:40:42 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 15:00:55 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg, size_t time )
{
	pthread_mutex_lock(&philo->init->print);
	if (check_death(philo) == 0)
		printf(msg, time, philo->id);
	pthread_mutex_unlock(&philo->init->print);
}

void	eat(t_philo *philo, long start)
{
	pthread_mutex_lock(philo -> left_fork);
	print_status(philo, "%ld %ld has taken a fork\n", get_time() - start);
	pthread_mutex_lock(philo -> right_fork);
	print_status(philo, "%ld %ld has taken a fork\n", get_time() - start);
	print_status(philo, "%ld %ld is eating\n", get_time() - start);
	pthread_mutex_lock(&philo -> meals_eating);
	philo -> last_meal = get_time();
	pthread_mutex_unlock(&philo -> meals_eating);
	pthread_mutex_lock(&philo -> meals_nums);
	philo -> meals_num++;
	pthread_mutex_unlock(&philo -> meals_nums);
	ft_sleep(philo -> init -> time_to_eat, philo);
	pthread_mutex_unlock(philo -> right_fork);
	pthread_mutex_unlock(philo -> left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_mutex	*data;

	data = ((t_philo *)arg)-> init;
	philo = (t_philo *)arg;
	if (philo->init->philos_num == 1)
	{
		print_status(philo, "%ld %ld has taken a fork\n",
			get_time() - philo->init->start);
		return (ft_sleep(philo->init->time_to_die, philo), NULL);
	}
	if (philo -> id % 2 == 0)
		ft_sleep (philo -> init -> time_to_eat, philo);
	while (check_death(philo) == 0)
	{
		eat(philo, data->start);
		ph_sleep(philo);
		think(philo);
	}
	return (NULL);
}

long	check_last_meal(t_philo *philo)
{
	long	meal;

	meal = 0;
	pthread_mutex_lock(&philo->meals_eating);
	meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meals_eating);
	return (meal);
}

int	check_philos_death(t_philo *philo)
{
	long	r;
	int		i;

	i = 0;
	while (i < philo->init->philos_num)
	{
		r = get_time() - check_last_meal(&philo[i]);
		if (r > philo->init->time_to_die)
		{
			print_status(&philo[i], "%ld %ld died\n",
				get_time() - philo->init->start);
			pthread_mutex_lock(&philo->init->death);
			philo->init->dead = 1;
			pthread_mutex_unlock(&philo->init->death);
			return (1);
		}
		i++;
	}
	return (0);
}
