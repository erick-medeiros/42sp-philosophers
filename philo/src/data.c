/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:35:44 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/15 16:45:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philosophers(t_data *data);
static t_bool	init_forks(t_data *data);
static t_bool	init_error(t_data *data);

t_bool	init_data(t_data *data, int argc, char *argv[])
{
	data->start_time = timestamp_in_ms();
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philosophers = NULL;
	data->forks = NULL;
	data->dinner_is_over = FALSE;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (init_error(data));
	if (pthread_mutex_init(&data->dinner_mutex, NULL) != 0)
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
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			pthread_mutex_destroy(&data->philosophers[i].last_meal_mutex);
			pthread_mutex_destroy(&data->philosophers[i].amount_of_meals_mutex);
		}
		free(data->philosophers);
	}
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
	t_philo	*philo;
	int		i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (data->philosophers == NULL)
		return (FALSE);
	memset(data->philosophers, 0, sizeof(t_philo) * data->num_of_philos);
	i = -1;
	while (++i < data->num_of_philos)
	{
		philo = &data->philosophers[i];
		philo->id = i;
		philo->num = i + 1;
		philo->is_pair = ((i + 1) % 2 != 0);
		philo->tid = 0;
		philo->data = data;
		philo->last_meal_time = data->start_time;
		philo->amount_of_meals = 0;
		if (pthread_mutex_init(&philo->last_meal_mutex, NULL) != 0)
			return (FALSE);
		if (pthread_mutex_init(&philo->amount_of_meals_mutex, NULL) != 0)
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	init_forks(t_data *data)
{
	t_philo	*philo;
	int		i;

	data->forks = malloc(sizeof(t_mutex) * (data->num_of_philos + 1));
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (FALSE);
		philo = &data->philosophers[i];
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[philo->num % data->num_of_philos];
		if (philo->is_pair)
		{
			philo->first_fork = philo->right_fork;
			philo->second_fork = philo->left_fork;
		}
		else
		{
			philo->first_fork = philo->left_fork;
			philo->second_fork = philo->right_fork;
		}
		++i;
	}
	return (TRUE);
}

static t_bool	init_error(t_data *data)
{
	destroy_data(data);
	return (FALSE);
}
