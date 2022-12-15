/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:27:04 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/15 17:02:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_amount_of_meals(t_philo *philo)
{
	int	amount;

	pthread_mutex_lock(&philo->last_meal_mutex);
	amount = philo->amount_of_meals;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (amount);
}

void	set_amount_of_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->amount_of_meals++;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

t_msec	get_last_meal_time(t_philo *philo)
{
	int	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = timestamp_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal);
}

void	set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
