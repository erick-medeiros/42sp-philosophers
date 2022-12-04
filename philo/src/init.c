/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:35:44 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/03 20:33:13 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philosophers(t_data *data);

t_bool	init_data(t_data *data, int argc, char *argv[])
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philosophers = NULL;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (FALSE);
	if (!init_philosophers(data))
		return (FALSE);
	return (TRUE);
}

static t_bool	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philosophers[i].number = i + 1;
		data->philosophers[i].tid = 0;
		++i;
	}
	return (TRUE);
}
