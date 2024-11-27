/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:34:59 by rallali           #+#    #+#             */
/*   Updated: 2024/11/19 13:36:39 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_result_overflow(long result, int sign)
{
	if (result > 2147483647 && sign == 1)
		return (1);
	if (result > 2147483648 && sign == -1)
		return (1);
	return (0);
}

long	ft_atoi(char *str)
{
	int			i;
	long		result;
	int			sign;
	long		tmp;

	result = 0;
	sign = 1;
	i = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (ft_result_overflow (result, sign) == 1)
			return (2147483648);
		tmp = result;
	}
	return (result * sign);
}
