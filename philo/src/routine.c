/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:12:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 12:49:03 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
	{
		state_log(philo, TAKE_FORK);
		return (0);
	}
	while (1)
	{
		if (philo_eat(philo))
			return (0);
		if (philo_sleep(philo))
			return (0);
		if (philo_think(philo))
			return (0);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (dinner_is_over(philo->data))
		return (-1);
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	if (dinner_is_over(philo->data))
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return (-1);
	}
	state_log(philo, TAKE_FORK);
	state_log(philo, TAKE_FORK);
	state_log(philo, EATING);
	update_info_of_meal(philo);
	ft_mssleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (dinner_is_over(philo->data))
		return (-1);
	state_log(philo, SLEEPING);
	ft_mssleep(philo->data->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (dinner_is_over(philo->data))
		return (-1);
	state_log(philo, THINKING);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!dinner_is_over(data))
	{
		i = -1;
		while (++i < data->num_of_philos)
			if (get_last_meal_time(&data->philosophers[i]) > data->time_to_die)
				return (announce_death(&data->philosophers[i]));
		ft_mssleep(5);
	}
	return (NULL);
}
