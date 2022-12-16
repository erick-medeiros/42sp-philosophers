/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:24:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/16 17:13:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	is_valid_number(char *str);

t_bool	check_arguments(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("philo: too few arguments\n");
		if (argc > 6)
			printf("philo: too many arguments\n");
		printf("usage: %s %s %s %s [%s]\n",
			"number_of_philosophers",
			"time_to_die",
			"time_to_eat",
			"time_to_sleep",
			"number_of_times_each_philosopher_must_eat");
		return (FALSE);
	}
	if (!argv)
		return (FALSE);
	while (*(++argv))
	{
		if (!is_valid_number(*argv))
		{
			printf("philo: %s: invalid argument\n", *argv);
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	is_valid_number(char *str)
{
	const char	*start = str;

	if (!str)
		return (FALSE);
	if (*str == '-')
		return (FALSE);
	if (*str == '+')
		++str;
	while (*str)
		if (!ft_isdigit(*str++))
			return (FALSE);
	if (ft_atoi(start) == 0)
		return (FALSE);
	return (TRUE);
}

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
