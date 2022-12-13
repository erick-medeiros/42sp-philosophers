/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:35:44 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/13 10:11:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philosophers(t_data *data);
static t_bool	init_forks(t_data *data);
static	t_bool	init_error(t_data *data);

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
	data->forks = NULL;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (init_error(data));
	if (!init_philosophers(data))
		return (init_error(data));
	if (!init_forks(data))
		return (init_error(data));
	return (TRUE);
}

void	destroy_data(t_data *data)
{
	int	i;

	if (data->philosophers)
		free(data->philosophers);
	if (data->forks)
	{
		i = -1;
		while (++i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->log_mutex);
}

static t_bool	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (data->philosophers == NULL)
		return (FALSE);
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].num = i + 1;
		data->philosophers[i].is_pair = ((i + 1) % 2 != 0);
		data->philosophers[i].tid = 0;
		data->philosophers[i].data = data;
	}
	return (TRUE);
}

static t_bool	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mutex) * (data->num_of_philos + 1));
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static	t_bool	init_error(t_data *data)
{
	destroy_data(data);
	return (FALSE);
}
