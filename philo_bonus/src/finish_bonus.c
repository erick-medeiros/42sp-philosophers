/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:46:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/16 18:21:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	dinner_is_over(t_data *data)
{
	t_bool	dinner;

	pthread_mutex_lock(&data->lock_dinner);
	dinner = data->dinner_is_over;
	pthread_mutex_unlock(&data->lock_dinner);
	return (dinner);
}

void	finish_dinner(t_data *data)
{
	pthread_mutex_lock(&data->lock_dinner);
	data->dinner_is_over = TRUE;
	pthread_mutex_unlock(&data->lock_dinner);
}
