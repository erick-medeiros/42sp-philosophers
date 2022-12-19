/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:27:04 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 15:14:23 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	update_info_of_meal(t_philo *philo)
{
	t_bool	ate_at_least;

	ate_at_least = FALSE;
	sem_wait(philo->lock_meal);
	philo->last_meal_time = timestamp_in_ms();
	philo->amount_of_meals++;
	if (philo->amount_of_meals == philo->data->must_eat)
		ate_at_least = TRUE;
	sem_post(philo->lock_meal);
	if (philo->data->must_eat > 0 && ate_at_least)
		sem_post(philo->data->lock_ate);
}

t_msec	get_last_meal_time(t_philo *philo)
{
	int	last_meal;

	sem_wait(philo->lock_meal);
	last_meal = timestamp_in_ms() - philo->last_meal_time;
	sem_post(philo->lock_meal);
	return (last_meal);
}

void	*all_ate_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->must_eat != -1)
	{
		i = -1;
		while (++i < data->num_of_philos)
			sem_wait(data->lock_ate);
		finish_dinner(data);
	}
	return (NULL);
}
