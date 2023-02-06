/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugurel <muhammedtalhaugurel@gmai...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:36:02 by mugurel           #+#    #+#             */
/*   Updated: 2023/02/02 23:36:03 by mugurel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reciver(int signum, siginfo_t *siginfo, void *unused)
{
	static int	c = 0;
	static int	byte = 7;

	(void)unused;
	if (signum == SIGUSR1)
		c += 1 << byte;
	else
		c += 0 << byte;
	if (byte == 0)
	{
		write(1, &c, 1);
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			ft_putstr_fd("ERROR\n", 1);
		c = 0;
		byte = 7;
	}
	else
		byte--;
}

int	main(void)
{
	struct sigaction	signal;
	int					error;
	pid_t				pid;

	ft_putstr_fd("PID => ", 1);
	pid = getpid();
	ft_putnbr(pid);
	ft_putstr_fd("\n", 1);
	signal.sa_sigaction = reciver;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_SIGINFO;
	error = sigaction(SIGUSR1, &signal, 0);
	error = sigaction(SIGUSR2, &signal, 0);
	if (error == -1)
		ft_putstr_fd("ERROR\n", 1);
	while (1)
		pause();
	return (0);
}
