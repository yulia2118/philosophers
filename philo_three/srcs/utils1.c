/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:25:31 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:53 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	ph_kill(t_ph **ph)
{
	int	i;

	i = 0;
	while (i < (*ph)->info->sum)
		kill((*ph + i++)->pid, SIGKILL);
}

char	*get_message(int message)
{
	if (message == FORK)
		return ("has taken a fork\n");
	else if (message == EAT)
		return ("is eating\n");
	else if (message == SLEEP)
		return ("is sleeping\n");
	else if (message == THINK)
		return ("is thinking\n");
	return ("died\n");
}

int	clean(t_ph **ph, int status)
{
	sem_unlink("forks");
	sem_unlink("sem");
	sem_unlink("print");
	sem_unlink("print_dead");
	if (*ph)
		free(*ph);
	if (status == EXIT_FAILURE)
		return (ft_putstr_fd("error: failure\n", 2));
	exit(EXIT_SUCCESS);
}

int	current_time(void)
{
	int						res;
	static struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (ERR_TIME);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}
