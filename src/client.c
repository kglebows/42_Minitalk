/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/08/24 15:47:02 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "libft/libft.h"

int main(int argn, char *argc[])
{
	int		server_pid;

	if (argn < 2)
		return (0);
	server_pid = ft_atoi(argc[1]);
	ft_printf("server PID: %d", server_pid);
	kill(server_pid, SIGUSR2);
	kill(server_pid, SIGUSR1);
	// kill(server_pid, SIGUSR2);
	// kill(server_pid, SIGUSR2);
	return (0);
}