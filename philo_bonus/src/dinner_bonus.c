/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:27:04 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:54:32 by eandre-f         ###   ########.fr       */
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
		ate_the_mandatory_meals(philo);
}

void	ate_the_mandatory_meals(t_philo *philo)
{
	int	all_ate;

	sem_wait(philo->data->lock_ate);
	sem_post(philo->data->all_ate);
	all_ate = *(int *)philo->data->all_ate;
	if (all_ate == philo->data->num_of_philos)
		finish_dinner(philo->data);
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
