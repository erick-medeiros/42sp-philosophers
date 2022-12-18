/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:09:23 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 19:49:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_mssleep(t_msec ms)
{
	t_msec	start;

	start = timestamp_in_ms();
	while (ms > timestamp_in_ms() - start)
		usleep(100);
	return (0);
}

t_msec	timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		write(fd, &(*s++), 1);
}
