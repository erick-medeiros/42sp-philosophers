/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:12:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/15 16:43:06 by eandre-f         ###   ########.fr       */
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
	if (philo->data->must_eat != -1
		&& get_amount_of_meals(philo) >= philo->data->must_eat)
	{
		finish_dinner(philo->data);
		return (-1);
	}
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
	set_last_meal_time(philo);
	set_amount_of_meals(philo);
	state_log(philo, EATING);
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
	long	last_meal;

	data = (t_data *)arg;
	while (1)
	{
		ft_mssleep(1);
		if (dinner_is_over(data))
			return (NULL);
		i = -1;
		while (++i < data->num_of_philos)
		{
			last_meal = get_last_meal_time(&data->philosophers[i]);
			if (last_meal > data->time_to_die)
			{
				state_log(&data->philosophers[i], DIED);
				finish_dinner(data);
				return (NULL);
			}
		}
	}
	return (NULL);
}
