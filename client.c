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

void	send_signal(int signum, unsigned char *message)
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
				kill(signum, SIGUSR1);
				message[c] = message[c] % i;
			}
			else
				kill(signum, SIGUSR2);
			usleep(1000);
			i /= 2;
		}
		i = 128;
		c++;
	}
}

void	feedback(int signum)
{
	static int	first_time = 1;

	(void)signum;
	if (first_time)
	{
		ft_putstr_fd("Mesaj başarıyla gönderildi!\n", 1);
		first_time = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	signal;
	pid_t					p_id;
	int 					error;

	signal.sa_flags = SA_SIGINFO;
	signal.sa_handler = feedback;
	error = sigaction(SIGUSR2, &signal, 0);
	if(error == -1)
		ft_putstr_fd("Fuck\n", 1);
	if (ac == 3)
	{
		p_id = ft_atoi(av[1]);
		send_signal(p_id, (unsigned char *)av[2]);
	}
	else if (ac == 3)
		ft_putstr_fd("Message pid is missing", 1);
	else
		ft_putstr_fd("Server pid is missing", 1);
	return (0);
}
