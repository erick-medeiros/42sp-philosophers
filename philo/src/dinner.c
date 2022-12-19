/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:27:04 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 10:11:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_info_of_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = timestamp_in_ms();
	philo->amount_of_meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

static int	get_amount_of_meals_remaining(t_philo *philo)
{
	int	amount;

	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->must_eat == -1)
		amount = -1;
	else
		amount = philo->data->must_eat - philo->amount_of_meals;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (amount);
}

t_msec	get_last_meal_time(t_philo *philo)
{
	int	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = timestamp_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal);
}

t_bool	everyone_finished_eating(t_data *data)
{
	t_bool	everyone_ate;
	int		i;

	everyone_ate = FALSE;
	if (data->must_eat != -1)
	{
		everyone_ate = TRUE;
		i = -1;
		while (++i < data->num_of_philos)
			if (get_amount_of_meals_remaining(&data->philosophers[i]) > 0)
				everyone_ate = FALSE;
	}
	return (everyone_ate);
}
