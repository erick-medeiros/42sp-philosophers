/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:41:45 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/15 15:35:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	const int	argc = 5;
	const char	*argv[] = {"./philo", "3", "500", "200", "200", 0};
	t_data		data;
	int			i;

	if (!check_arguments(argc, (char **)argv))
		return (EXIT_FAILURE);
	if (!init_data(&data, argc, (char **)argv))
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
