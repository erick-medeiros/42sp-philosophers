/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:51:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/12 19:29:52 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_log(t_philo *philo, const char *state)
{
	const int	timestamp_in_ms = 0;

	pthread_mutex_lock(&philo->data->log_mutex);
	printf("%d %d %s\n", timestamp_in_ms, philo->id, state);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
