/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:24:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/03 15:38:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
