/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:12:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/12 19:35:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_think(philo);
	philo_eat(philo);
	philo_sleep(philo);
	return (NULL);
}

t_bool	philo_eat(t_philo *philo)
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = &philo->data->forks[philo->id];
	right_fork = &philo->data->forks[(philo->id + 1)
		% philo->data->num_of_philos];
	pthread_mutex_lock(left_fork);
	state_log(philo, "has taken a fork");
	pthread_mutex_lock(right_fork);
	state_log(philo, "has taken a fork");
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	state_log(philo, "is eating");
	return (TRUE);
}

t_bool	philo_think(t_philo *philo)
{
	state_log(philo, "is thinking");
	return (TRUE);
}

t_bool	philo_sleep(t_philo *philo)
{
	state_log(philo, "is sleeping");
	return (TRUE);
}

t_bool	philo_died(t_philo *philo)
{
	state_log(philo, "died");
	return (TRUE);
}
