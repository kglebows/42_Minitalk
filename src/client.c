/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/26 17:45:08 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

void act(int signo)
{
	if (signo == SIGUSR2)
		ft_printf("delivered!");
}

int main(int argn, char *argc[])
{
	int						server_pid;
	char					c;
	int						i;
	struct sigaction		action;

	if (argn != 2)
		return (0);
	server_pid = ft_atoi(argc[1]);
	action.sa_handler = act;
	while (*argc[2])
	{
		c = *argc[2]++;
		i = 8;
		while (i--)
		{
			if (c >> i & 1)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(100);
		}
		sigaction(SIGUSR2, &action, NULL);
	}
	i = 8;
	while (i--)
	{
		kill(server_pid, SIGUSR1);
		usleep(100);
	}
	return (0);
}
