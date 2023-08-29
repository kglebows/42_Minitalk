/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/30 01:09:20 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	g_pause;

void	send_chunk(int server_pid, unsigned char chunk)
{
	int				i;

	i = 8;
	while (i--)
	{
		g_pause = 1;
		if (chunk >> i & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		while (g_pause == 1)
			continue ;
		usleep(100);
	}
}

void	act(int signo)
{
	if (signo == SIGUSR1)
		g_pause = 0;
	if (signo == SIGUSR2)
		ft_printf(" :: Message received! :: \n");
}

int	ft_isnumber(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argn, char *argc[])
{
	int						server_pid;
	static char				c;
	struct sigaction		action;

	if (argn < 3)
		return (ft_printf("Wrong input! Missing message or PID!\n") * 0 + 2);
	if (argn > 3)
		return (ft_printf("Wrong input! Too many arguments!\n") * 0 + 2);
	if (!ft_isnumber(argc[1]))
		return (ft_printf("Wrong input! Missing PID!\n") * 0 + 2);
	server_pid = ft_atoi(argc[1]);
	action.sa_handler = act;
	action.sa_flags = 0;
	sigaction(SIGUSR2, &action, NULL);
	sigaction(SIGUSR1, &action, NULL);
	while (*argc[2])
	{
		c = *argc[2]++;
		send_chunk(server_pid, c);
	}
	send_chunk(server_pid, 0);
	return (0);
}
