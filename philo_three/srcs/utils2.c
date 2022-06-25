/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:26:31 by fdarrin           #+#    #+#             */
/*   Updated: 2021/04/10 15:34:43 by fdarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	res;
	int		min;

	min = 0;
	if (n == -2147483648)
	{
		min++;
		n++;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * (-1);
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	res = (n % 10) + 48;
	if (min == 1)
		res = 56;
	write(fd, &res, 1);
}

int	my_atoi(char *str, int *res)
{
	*res = 0;
	if (*str == '\0')
		return (-1);
	while (*str && *str >= '0' && *str <= '9')
		*res = 10 * (*res) + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}

void	my_usleep(int msec)
{
	int	start;

	start = current_time();
	while (current_time() - start < msec)
		usleep(500);
}
