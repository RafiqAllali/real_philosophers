/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:50:02 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 14:35:27 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_death(t_philo *philo)
{
	int	death;

	death = 0 ;
	pthread_mutex_lock(&philo->init->death);
	death = philo->init->dead;
	pthread_mutex_unlock(&philo->init->death);
	return (death);
}

void	ft_sleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_death(philo))
			return ;
		usleep(10);
	}
}

void	think(t_philo *philo)
{
	long	current;

	current = get_time() - philo->init->start;
	print_status(philo, "%ld %ld is thinking\n", current);
}

void	ph_sleep(t_philo *philo)
{
	long	current;

	current = get_time() - philo->init->start;
	print_status(philo, "%ld %ld is sleeping\n", current);
	ft_sleep (philo -> init -> time_to_sleep, philo);
}
