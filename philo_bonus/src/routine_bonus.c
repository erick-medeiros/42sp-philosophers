/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:12:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 22:58:10 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	pthread_create(&philo->monitor_tid, NULL, monitor_routine, (void *)philo);
	pthread_create(&philo->dinner_tid, NULL, dinner_routine, (void *)philo);
	sem_wait(philo->data->lock_dinner);
	sem_post(philo->data->lock_dinner);
	pthread_detach(philo->dinner_tid);
	pthread_detach(philo->monitor_tid);
	destroy_data(philo->data, FALSE);
	exit(0);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
	{
		state_log(philo->data, philo->num, TAKE_FORK);
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
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	if (dinner_is_over(philo->data))
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		return (-1);
	}
	state_log(philo->data, philo->num, TAKE_FORK);
	state_log(philo->data, philo->num, TAKE_FORK);
	update_info_of_meal(philo);
	state_log(philo->data, philo->num, EATING);
	ft_mssleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (dinner_is_over(philo->data))
		return (-1);
	state_log(philo->data, philo->num, SLEEPING);
	ft_mssleep(philo->data->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (dinner_is_over(philo->data))
		return (-1);
	state_log(philo->data, philo->num, THINKING);
	return (0);
}
