/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:12:46 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/24 15:43:16 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

void act(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_printf("GOT SIGUSR1!!! from %d\n", siginfo->si_pid);
	}
	if (signo == SIGUSR2)
	{
		ft_printf("GOT SIGUSR2!! from %d\n", siginfo->si_pid);
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
