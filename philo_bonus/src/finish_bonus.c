/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:46:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:12:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!dinner_is_over(philo->data))
	{
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

	dinner = FALSE;
	sem_wait(data->lock_dinner);
	if (*(int *)data->dinner_is_over > 0)
		dinner = TRUE;
	sem_post(data->lock_dinner);
	return (dinner);
}

void	finish_dinner(t_data *data)
{
	sem_wait(data->lock_dinner);
	sem_post(data->dinner_is_over);
	sem_post(data->lock_dinner);
}

void	exit_error(t_data *data, t_bool delete_sem, char *msg)
{
	destroy_data(data, delete_sem);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
