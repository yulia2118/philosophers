/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:14:57 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:29 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	print(t_ph *ph, int message)
{
	sem_wait(ph->info->print_sem);
	printf("%d %d %s", (int)(current_time() - ph->info->start), ph->number, \
		get_message(message));
	sem_post(ph->info->print_sem);
}

void	take_meal(t_ph *ph)
{
	if (ph->info->dead || (ph->info->meals && ph->meals == ph->info->meals))
		return ;
	sem_wait(ph->info->forks);
	print(ph, FORK);
	sem_wait(ph->info->forks);
	print(ph, FORK);
	sem_wait(ph->info->semaphor);
	ph->last_meal = current_time() + ph->info->time_to_die;
	print(ph, EAT);
	sem_post(ph->info->semaphor);
	ph->meals += 1;
	my_usleep(ph->info->time_to_eat);
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
	print(ph, SLEEP);
	my_usleep(ph->info->time_to_sleep);
}

void	*check_work(void *v_ph)
{
	t_info	*info;
	t_ph	*ph;

	ph = (t_ph *)v_ph;
	info = ph->info;
	pthread_detach(ph->check_thread);
	while (info->meals == 0 || info->meals != ph->meals)
	{
		sem_wait(info->semaphor);
		sem_wait(info->print_dead_sem);
		if (current_time() > ph->last_meal)
		{
			print(ph, DEAD);
			info->dead = 1;
			sem_post(info->semaphor);
			exit(DEAD);
		}
		sem_post(info->print_dead_sem);
		sem_post(info->semaphor);
		usleep(1000);
	}
	return (NULL);
}

void	work(t_ph *ph)
{
	t_info	*info;
	int		time;

	info = ph->info;
	time = current_time();
	if (time == 1)
		exit(EXIT_FAILURE);
	ph->last_meal = time + ph->info->time_to_die;
	if (pthread_create(&ph->check_thread, NULL, &check_work, (void *)ph))
		exit(EXIT_FAILURE);
	if (ph->number % 2 == 0)
		my_usleep(info->time_to_eat);
	while (ph->info->dead == 0)
	{
		if (ph->info->meals == 0 || ph->info->meals != ph->meals)
		{
			take_meal(ph);
			print(ph, THINK);
		}
		else
			break ;
	}
	exit(EXIT_SUCCESS);
}

int	start(t_ph **ph)
{
	int	i;

	i = 0;
	(*ph)->info->start = current_time();
	if ((*ph)->info->start == 1)
		return (EXIT_FAILURE);
	while (i < (*ph)->info->sum)
	{
		(*ph + i)->pid = fork();
		if ((*ph + i)->pid < 0)
		{
			ph_kill(ph);
			return (EXIT_FAILURE);
		}
		else if ((*ph + i)->pid == 0)
			work(*ph + i);
		i++;
	}
	return (EXIT_SUCCESS);
}
