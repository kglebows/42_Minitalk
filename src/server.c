/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:12:46 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/25 22:03:21 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

void act(int signo, siginfo_t *siginfo, void *context)
{
	int					server_pid;
	static unsigned char			c = 0;
	static int			i = 0;

	(void)context;
	server_pid = siginfo->si_pid;
	if (signo == SIGUSR1)
	{
		ft_printf("0");
	}
	if (signo == SIGUSR2)
	{
		ft_printf("1");
	}
	c |= (signo == SIGUSR2);
	if (++i != 8)
	{
		c <<= 1;
	}
	else
	{
		ft_printf("%c", c);
		ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
	
}

int main(void)
{
	struct sigaction		action;

	ft_printf("PID: %d\n", getpid());
	action.sa_sigaction = act; 
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		continue ;
	return (0);
}
