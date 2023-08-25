/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/25 21:50:21 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

int main(int argn, char *argc[])
{
	int			server_pid;
	char		c;
	int			i;

	if (argn < 2)
		return (0);
	server_pid = ft_atoi(argc[1]);
	// ft_printf("server PID: %d", server_pid);
	while (*argc[2])
	{
		c = *argc[2]++;
		i = 8;
		while (i--)
		{
			if (c >> i & 1)
			{
				ft_printf("1");
				kill(server_pid, SIGUSR2);
			}
			else
			{
				ft_printf("0");
				kill(server_pid, SIGUSR1);
			}
			usleep(100);
		}
		ft_printf("%c", c);
	}
	return (0);
}
