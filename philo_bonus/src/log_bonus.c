/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:51:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/16 18:20:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	state_log(t_philo *philo, t_state state)
{
	t_msec	timestamp;
	char	*str;

	pthread_mutex_lock(&philo->data->lock_log);
	timestamp = timestamp_in_ms() - philo->data->start_time;
	str = NULL;
	if (state == TAKE_FORK && !dinner_is_over(philo->data))
		str = "has taken a fork";
	else if (state == EATING && !dinner_is_over(philo->data))
		str = "is eating";
	else if (state == SLEEPING && !dinner_is_over(philo->data))
		str = "is sleeping";
	else if (state == THINKING && !dinner_is_over(philo->data))
		str = "is thinking";
	else if (state == DIED)
		str = "died";
	if (str)
		printf("%5li %2i %s\n", timestamp, philo->num, str);
	pthread_mutex_unlock(&philo->data->lock_log);
}
