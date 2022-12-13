/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:51:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/13 11:49:44 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_log(t_philo *philo, const char *state)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->log_mutex);
	timestamp = timestamp_in_ms() - philo->data->start_time;
	printf("%li %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
