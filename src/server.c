/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:12:46 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/26 17:41:06 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

void act(int signo, siginfo_t *siginfo, void *context)
{
	static unsigned char			c = 0;
	static int						i = 0;

	(void)context;
	c |= (signo == SIGUSR2);
	if (++i != 8)
		c <<= 1;
	else
	{
		if (!c)
			kill(siginfo->si_pid, SIGUSR2);
		ft_printf("%c", c);
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
