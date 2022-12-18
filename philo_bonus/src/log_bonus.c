/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:51:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 18:25:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	state_log(t_data *data, int philo_num, t_state state)
{
	t_msec	timestamp;
	char	*str;

	sem_wait(data->lock_log);
	timestamp = timestamp_in_ms() - data->start_time;
	str = NULL;
	if (state == TAKE_FORK && !dinner_is_over(data))
		str = "has taken a fork";
	else if (state == EATING && !dinner_is_over(data))
		str = "is eating";
	else if (state == SLEEPING && !dinner_is_over(data))
		str = "is sleeping";
	else if (state == THINKING && !dinner_is_over(data))
		str = "is thinking";
	else if (state == DIED)
		str = "died";
	if (str)
		printf("%5li %2i %s\n", timestamp, philo_num, str);
	sem_post(data->lock_log);
}
