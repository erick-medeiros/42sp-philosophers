/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:27:04 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 14:44:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_info_of_meal(t_philo *philo)
{
	t_bool	ate_at_least;

	ate_at_least = FALSE;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = timestamp_in_ms();
	philo->amount_of_meals++;
	if (philo->amount_of_meals == philo->data->must_eat)
		ate_at_least = TRUE;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->data->must_eat > 0 && ate_at_least)
	{
		pthread_mutex_lock(&philo->data->all_ate_mutex);
		philo->data->how_many_ate++;
		if (philo->data->how_many_ate == philo->data->num_of_philos)
			finish_dinner(philo->data);
		pthread_mutex_unlock(&philo->data->all_ate_mutex);
	}
}

t_msec	get_last_meal_time(t_philo *philo)
{
	int	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = timestamp_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal);
}
