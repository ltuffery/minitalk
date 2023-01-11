/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:41:18 by ltuffery          #+#    #+#             */
/*   Updated: 2023/01/11 18:09:49 by ltuffery         ###   ########.fr       */
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

static char	*join(char *str, char c)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

static char	*get_message(siginfo_t *info, char *msg, char *bit, int *i)
{
	msg = join(msg, (char)*bit);
	if ((char)*bit == '\0')
	{
		ft_putstr_fd(msg, 1);
		free(msg);
		msg = NULL;
		*i = 0;
		*bit = 0;
		kill(info->si_pid, SIGUSR1);
		return (msg);
	}
	*i = 0;
	*bit = 0;
	return (msg);
}

void	listen(int sig, siginfo_t *info, void *unused)
{
	static int	i;
	static int	bit;
	static char	*message;

	(void) unused;
	if (message == NULL)
		message = ft_calloc(1, 1);
	if (message == NULL)
		return ;
	if (i == 8)
	{
		if ((char)bit == '\0')
		{
			message = get_message(info, message, (char *)&bit, &i);
			return ;
		}
		message = get_message(info, message, (char *)&bit, &i);
	}
	else
	{
		if (sig == SIGUSR2)
			bit += ft_pow(2, i);
		i++;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = listen;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
	{
	}
}
