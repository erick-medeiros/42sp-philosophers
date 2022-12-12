/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:12:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/04 14:39:10 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo_eat(philo);
	philo_think(philo);
	philo_sleep(philo);
	return (NULL);
}

t_bool	philo_eat(t_philo *philo)
{
	state_log(philo, "has taken a fork");
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
