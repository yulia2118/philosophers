/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:24:26 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:09 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	init_options(t_info *info, int argc, char **argv)
{
	if (my_atoi(argv[1], (int *)&info->sum) != 0 || \
		my_atoi(argv[2], &info->time_to_die) != 0 || \
			my_atoi(argv[3], &info->time_to_eat) != 0 || \
				my_atoi(argv[4], &info->time_to_sleep) != 0)
		return (ERR_ARGS);
	if (argc == 6 && my_atoi(argv[5], (int *)&info->meals) != 0)
		return (ERR_ARGS);
	else if (argc == 5)
		info->meals = 0;
	if (info->sum < 2 || info->sum > 200 || info->time_to_die < 60 || \
		info->time_to_eat < 60 || info->time_to_sleep < 60 || info->meals < 0)
		return (ERR_ARGS);
	info->dead = 0;
	return (EXIT_SUCCESS);
}

int	init_mtxs(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->mutex_print, NULL) || \
		pthread_mutex_init(&info->mutex, NULL))
		return (ERR_MUTEX);
	info->frks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->sum);
	if (!(info->frks))
		return (ERR_MALLOC);
	while (i < info->sum)
	{
		if (pthread_mutex_init(&info->frks[i++], NULL))
			return (ERR_MUTEX);
	}
	return (EXIT_SUCCESS);
}

int	init_ph(t_info *info, t_ph **ph)
{
	int	i;

	i = 0;
	*ph = (t_ph *)malloc(sizeof(t_ph) * info->sum);
	if (!(*ph))
		return (ERR_MALLOC);
	while (i < info->sum)
	{
		(*ph)[i].number = i + 1;
		(*ph)[i].meals = 0;
		(*ph)[i].left_fork = &info->frks[i];
		(*ph)[i].right_fork = &info->frks[(i + 1) % info->sum];
		(*ph)[i].info = info;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_ph	*ph;
	int		i;

	i = 0;
	if ((5 > argc) || (argc > 6) || (init_options(&info, argc, argv)))
		return (ft_putstr_fd("bad arguments\n", 2));
	if (init_mtxs(&info) || init_ph(&info, &ph) || start(&ph))
		return (clean(&ph, EXIT_FAILURE));
	while (i < info.sum)
		pthread_join((ph + i++)->thread, NULL);
	return (clean(&ph, EXIT_SUCCESS));
}
