/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:41:45 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/04 10:53:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	const int	argc = 5;
	const char	*argv[] = {"1", "1", "1", "1", 0};
	t_data		data;

	if (!check_arguments(argc, (char **)argv))
		return (EXIT_FAILURE);
	if (!init_data(&data, argc, (char **)argv))
		return (EXIT_FAILURE);
	pthread_create(&data.philosophers[0].tid,
		NULL, dinner_routine, (void *)(data.philosophers));
	pthread_join(data.philosophers[0].tid, NULL);
	destroy_data(&data);
	return (EXIT_SUCCESS);
}
