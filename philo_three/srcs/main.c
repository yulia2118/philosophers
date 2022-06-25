/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:21:26 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:09 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	res(t_ph **ph, t_info *info)
{
	int	status;
	int	i;

	i = 0;
	while (i < info->sum)
	{
		if (waitpid(-1, &status, 0) == -1)
			return (EXIT_FAILURE);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				ph_kill(ph);
				return (EXIT_FAILURE);
			}
			else if (WEXITSTATUS(status) == DEAD)
				ph_kill(ph);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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

int	init_sem(t_info *info)
{
	sem_unlink("forks");
	info->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, info->sum);
	sem_unlink("sem");
	info->semaphor = sem_open("sem", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("print");
	info->print_sem = sem_open("print", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("print_dead");
	info->print_dead_sem = sem_open("print_dead", O_CREAT | O_EXCL, 0777, 1);
	if (!(info->forks) || !(info->print_sem) || !(info->semaphor) \
		|| !(info->print_dead_sem))
		return (EXIT_FAILURE);
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
		(*ph)[i].info = info;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_ph	*ph;

	if ((5 > argc) || (argc > 6) || (init_options(&info, argc, argv)))
		return (ft_putstr_fd("bad arguments\n", 2));
	if (init_sem(&info) || init_ph(&info, &ph) || start(&ph) || res(&ph, &info))
		return (clean(&ph, EXIT_FAILURE));
	return (clean(&ph, EXIT_SUCCESS));
}
