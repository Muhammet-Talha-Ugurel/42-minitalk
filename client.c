/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugurel <muhammedtalhaugurel@gmai...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:34:23 by mugurel           #+#    #+#             */
/*   Updated: 2023/02/02 23:34:24 by mugurel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_it(int signal, pid_t pid)
{
	if (kill(pid, signal) == -1)
	{
		ft_putstr_fd("ERROR\n", 1);
		return (0);
	}
	return (1);
}

void	send(pid_t pid, unsigned char *message)
{
	int	i;
	int	c;

	c = 0;
	i = 128;
	while (message[c])
	{
		while (i >= 1)
		{
			if (message[c] / i)
			{
				if (send_it(SIGUSR1, pid) == 0)
					return ;
				message[c] = message[c] % i;
			}
			else if (send_it(SIGUSR2, pid) == 0)
				return ;
			usleep(5000);
			i /= 2;
		}
		i = 128;
		c++;
	}
}

void	feedback(int signum)
{
	static int	flag = 1;

	if (flag && signum == SIGUSR2)
	{
		ft_putstr_fd("SUCESS!\n", 1);
		flag = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	signal;
	pid_t				p_id;
	int					error;

	signal.sa_flags = SA_SIGINFO;
	signal.sa_handler = feedback;
	error = sigaction(SIGUSR2, &signal, 0);
	if (error == -1)
		ft_putstr_fd("ERROR\n", 1);
	if (ac == 3)
	{
		p_id = ft_atoi(av[1]);
		send(p_id, (unsigned char *)av[2]);
	}
	else if (ac == 2)
		ft_putstr_fd("Message is missing", 1);
	else
		ft_putstr_fd("Server pid is missing", 1);
	return (0);
}
