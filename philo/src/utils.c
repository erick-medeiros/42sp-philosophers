/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:09:23 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/03 15:18:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sin;
	long	val;
	long	pre;

	if (!str)
		return (0);
	sin = 1;
	val = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sin = -1;
	while (ft_isdigit(*str))
	{
		pre = val;
		val = (val * 10) + (*str++ - '0');
		if (val < pre)
		{
			if (sin == 1)
				return (-1);
			return (0);
		}
	}
	return (val * sin);
}
