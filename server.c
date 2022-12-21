/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:14:59 by ltuffery          #+#    #+#             */
/*   Updated: 2022/12/21 18:43:58 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <bits/types/siginfo_t.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

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

void	ft_putstr(char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		write(1, &message[i], 1);
		i++;
	}
}

char	*get_and_put_message(char *message, int bit, int *j)
{
	if (bit != 0)
	{
		message[*j] = (char) bit;
		(*j)++;
		return (message);
	}
	message[*j] = '\0';
	*j = 0;
	ft_putstr(message);
	free(message);
	return (NULL);
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	static int	i;
	static int	j;
	static int	bit;
	static char	*message;

	(void) unused;
	if (message == NULL)
		message = malloc(sizeof(char *) * (sizeof(size_t) * 8 + 1));
	if (message == NULL)
		return ;
	if ((sig == SIGUSR2 || sig == SIGUSR1))
	{
		if (sig == SIGUSR2)
			bit += ft_pow(2, 7 - i);
		i++;
	}
	if (i == 8)
	{
		message = get_and_put_message(message, bit, &j);
		if (message == NULL)
			kill(info->si_pid, SIGUSR1);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = listen;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	printf("PID: %i\n\n", pid);
	while (1)
	{
	}
	return (0);
}
