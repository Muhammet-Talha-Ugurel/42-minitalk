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

	static int	character = 0;
	static int	index = 7;
	int			c;

	(void)unused;
	if (signum == SIGUSR1)
		c = 1;
	else
		c = 0;
	character += c << index;
	if (index == 0)
	{
		write(1, &character, 1);
		character = 0;
		index = 7;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			ft_putstr_fd("Sinyal Gönderme Hatası\n", 1);
	}
	else
		index--;
}

int	main(void)
{
	struct sigaction	signal;
	int						error;
	pid_t					pid;

	pid = getpid();
	ft_putnbr(pid);
	signal.sa_sigaction = reciver;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_SIGINFO;
	error = sigaction(SIGUSR1, &signal, 0);
	error = sigaction(SIGUSR2, &signal, 0);
	if (error == -1)
		ft_putstr_fd("Fuck", 1);
	while (1)
		pause();
	return (0);
}
