/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:35:44 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/19 16:50:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	init_philosophers(t_data *data);
static t_bool	init_error(t_data *data);

t_bool	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	data->start_time = timestamp_in_ms();
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philosophers = NULL;
	data->forks = new_semaphore("/forks", data->num_of_philos);
	data->lock_log = new_semaphore("/log", 1);
	data->lock_dinner = new_semaphore("/dinner", 1);
	data->dinner_is_over = new_semaphore("/dinner_is_over", 0);
	data->lock_ate = new_semaphore("/ate", 1);
	data->all_ate = new_semaphore("/all_ate", 0);
	if (!init_philosophers(data))
		return (init_error(data));
	return (TRUE);
}

static t_bool	init_philosophers(t_data *data)
{
	t_philo	*philo;
	int		i;

	data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
	if (data->philosophers == NULL)
		return (FALSE);
	i = -1;
	while (++i < data->num_of_philos)
	{
		philo = &data->philosophers[i];
		philo->id = i;
		philo->pid = 0;
		philo->num = i + 1;
		philo->monitor_tid = 0;
		philo->dinner_tid = 0;
		philo->data = data;
		philo->last_meal_time = data->start_time;
		philo->amount_of_meals = 0;
		philo->sem_name = philo_sem_name("/philo_meal_", philo->num);
		philo->lock_meal = new_semaphore(philo->sem_name, 1);
	}
	return (TRUE);
}

static void	destroy_data_delete_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/log");
	sem_unlink("/dinner");
	sem_unlink("/dinner_is_over");
	sem_unlink("/ate");
}

void	destroy_data(t_data *data, t_bool delete_sem)
{
	int	i;

	if (data->philosophers)
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			sem_close(data->philosophers[i].lock_meal);
			if (delete_sem)
				sem_unlink(data->philosophers[i].sem_name);
			free(data->philosophers[i].sem_name);
		}
		free(data->philosophers);
	}
	sem_close(data->forks);
	sem_close(data->lock_log);
	sem_close(data->lock_dinner);
	sem_close(data->lock_ate);
	sem_close(data->dinner_is_over);
	if (delete_sem)
		destroy_data_delete_sem();
}

static t_bool	init_error(t_data *data)
{
	destroy_data(data, TRUE);
	return (FALSE);
}
