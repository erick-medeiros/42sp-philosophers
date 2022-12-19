/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:46:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 13:03:38 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	dinner_is_over(t_data *data)
{
	t_bool	dinner;

	pthread_mutex_lock(&data->dinner_mutex);
	dinner = data->dinner_is_over;
	pthread_mutex_unlock(&data->dinner_mutex);
	return (dinner);
}

void	*finish_dinner(t_data *data)
{
	pthread_mutex_lock(&data->dinner_mutex);
	data->dinner_is_over = TRUE;
	pthread_mutex_unlock(&data->dinner_mutex);
	return (0);
}

void	*announce_death(t_philo *philo)
{
	state_log(philo, DIED);
	return (finish_dinner(philo->data));
}
