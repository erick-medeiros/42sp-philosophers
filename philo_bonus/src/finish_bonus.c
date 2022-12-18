/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:46:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/17 23:02:04 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->must_eat != -1)
		{
			if (get_amount_of_meals_remaining(philo) == 0)
				sem_post(philo->data->lock_ate);
		}
		if (get_last_meal_time(philo) > philo->data->time_to_die)
		{
			state_log(philo->data, philo->num, DIED);
			finish_dinner(philo->data);
			return (NULL);
		}
		ft_mssleep(5);
	}
	return (NULL);
}

t_bool	dinner_is_over(t_data *data)
{
	t_bool	dinner;

	dinner = *(int *)data->lock_dinner;
	return (dinner);
}

void	finish_dinner(t_data *data)
{
	sem_post(data->lock_dinner);
}

void	exit_error(t_data *data, t_bool delete_sem, char *msg)
{
	destroy_data(data, delete_sem);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
