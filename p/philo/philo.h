/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:27:14 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 21:10:07 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mutex
{
	pthread_mutex_t	fork[200];
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int				philos_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	int				dead;
	long			start;
}	t_mutex;

typedef struct s_philo
{
	long			id;
	long			last_meal;
	int				meals_num;
	t_mutex			*init;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_eating;
	pthread_mutex_t	meals_nums;

}	t_philo;

int		ft_strlen(char **str);
long	ft_atoi(char *str);
void	print_status(t_philo *philo, char *msg, size_t time );
int		check_death(t_philo *philo);
long	get_time(void);
void	ft_sleep(size_t time, t_philo *philo);
void	think(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	*routine(void *arg);
int		parse(char **av, int ac);
int		check_philos_death(t_philo *philo);
void	init_meals(t_mutex *params, t_philo *philo);
void	create_philos(t_mutex *params, t_philo *philo, pthread_t *th);
int		monitor_death(t_philo *philo);
void	join_philos(pthread_t *th, t_mutex *params);
void	destroy(t_mutex *params);
#endif