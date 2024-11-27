/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:35:02 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 16:54:54 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_num(char *num)
{
	int	i;

	i = 0;
	while (num[i] == ' ')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	num(char **av, int ac)
{
	long	v;
	int		i;

	if (ac < 5)
		return (1);
	i = 1;
	while (i < ac)
	{
		v = ft_atoi(av[i]);
		if (v >= 2147483648 || v < 0)
			return (1);
		if (i == 1 && (v <= 0 || v > 200))
			return (1);
		if (i > 1 && i != 5 && v < 60)
			return (1);
		i++;
	}
	return (0);
}

int	ft_space(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '\0')
			return (1);
		while (av[i][j] && av[i][j] == ' ')
			j++;
		if (!av[i][j])
			return (1);
		i++;
	}
	return (0);
}

int	parse(char **av, int ac)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_num(av[i]) == 1 || ft_space(av, ac) == 1)
			return (1);
		i++;
	}
	if (num (av, ac) == 1)
		return (1);
	return (0);
}
