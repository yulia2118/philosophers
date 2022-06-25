/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:30:11 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:53 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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
	else if (message == DEAD)
		return ("died\n");
	return ("\n");
}

int	clean(t_ph **ph, int status)
{
	int	i;

	pthread_mutex_destroy(&(*ph)->info->mutex);
	pthread_mutex_destroy(&(*ph)->info->mutex_print);
	if (*ph)
	{
		if ((*ph)->info->frks)
		{
			i = 0;
			while (i < (*ph)->info->sum)
				pthread_mutex_destroy(&(*ph)->info->frks[i++]);
			free((*ph)->info->frks);
		}
		free(*ph);
	}
	if (status == EXIT_FAILURE)
		return (ft_putstr_fd("error: failure\n", 2));
	return (status);
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
