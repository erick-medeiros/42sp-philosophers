/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:41:45 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/15 16:47:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (!check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < data.num_of_philos)
		pthread_create(&data.philosophers[i].tid,
			NULL, dinner_routine, (void *)&data.philosophers[i]);
	pthread_create(&data.monitor_tid, NULL, monitor_routine, (void *)&data);
	i = -1;
	while (++i < data.num_of_philos)
		pthread_join(data.philosophers[i].tid, NULL);
	pthread_join(data.monitor_tid, NULL);
	destroy_data(&data);
	return (EXIT_SUCCESS);
}
