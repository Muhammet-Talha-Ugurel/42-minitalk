/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugurel <muhammedtalhaugurel@gmai...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:36:07 by mugurel           #+#    #+#             */
/*   Updated: 2023/02/02 23:36:08 by mugurel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	index;
	int	num;

	index = 0;
	num = 0;
	while (str[index] != '\0')
	{
		num *= 10;
		num += str[index] - 48;
		index++;
	}
	return (num);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], fd);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(1, &c, fd);
}

void	ft_putnbr(int nb)
{
	if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + 48, 1);
	else if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar_fd(nb % 10 + 48, 1);
	}
}
