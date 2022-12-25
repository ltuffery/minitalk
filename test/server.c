/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:41:18 by ltuffery          #+#    #+#             */
/*   Updated: 2022/12/25 00:57:31 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <bits/types/siginfo_t.h>
#include <signal.h>

int	ft_pow(int nb, int power)
{
	int	i;
	int	total;

	i = 1;
	total = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (i < power)
	{
		total *= nb;
		i++;
	}
	return (total);
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	static int	i;
	static int	j;
	static int	bit;
	static char	*message;

	if (message == NULL)
		message = malloc(sizeof(size_t) * 8 + 1);
	if (message == NULL)
		return ;
	if (i == 8)
	{
		message[j] = bit;
		if ((char)bit == '\0')
		{
			ft_putstr_fd(message, 1);
			free(message);
			message = NULL;
			j = 0;
			i = 0;
			bit = 0;
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		j++;
		i = 0;
		bit = 0;
	}
	else
	{
		if (sig == SIGUSR2)
			bit += ft_pow(2, i);
		i++;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	act.sa_sigaction = listen;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
	{
	}
}
