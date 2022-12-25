/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:39:45 by ltuffery          #+#    #+#             */
/*   Updated: 2022/12/25 00:50:29 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>

void	send(int pid, char *message);

void	listen(int sig, siginfo_t *info, void *unused)
{
	(void)unused;
	if (sig == SIGUSR2)
		send(info->si_pid, NULL);
	else if (sig == SIGUSR1)
	{
		ft_putendl_fd("Message bien recue\n", 1);
		exit(0);
	}
}

void	send(int pid, char *message)
{
	static char	*msg;
	static int	i;
	static int	j;

	if (msg == NULL && message != NULL)
		msg = message;
	if (msg[i] & (1 << j))
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	if (j == 8)
	{
		j = 0;
		i++;
	}
	else
		j++;
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	if (ac != 3)
		return (0);
	act.sa_sigaction = listen;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	send(ft_atoi(av[1]), av[2]);
	while (1)
	{
	}
}
