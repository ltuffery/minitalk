/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:02:23 by ltuffery          #+#    #+#             */
/*   Updated: 2022/12/24 23:55:14 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	g_message_is_send = 0;

void	send_end_string(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

void	send(char *str, int pid)
{
	int	i;
	int	bit;

	i = 0;
	while ((unsigned char)str[i] != '\0')
	{
		bit = 7;
		while (bit > -1)
		{
			if ((unsigned char)str[i] & (1 << bit))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			bit--;
		}
		i++;
	}
	g_message_is_send = 1;
	send_end_string(pid);
}

void	listen(int sig)
{
	if (g_message_is_send == 1 && sig == SIGUSR1)
	{
		g_message_is_send = 0;
		ft_putendl_fd("Recu", 1);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	act;

	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	act.sa_handler = &listen;
	sigaction(SIGUSR1, &act, NULL);
	send(av[2], pid);
	while (1)
	{
	}
}
