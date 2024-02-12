/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awacowsk <awacowsk@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:47:14 by awacowsk          #+#    #+#             */
/*   Updated: 2024/02/02 21:57:08 by awacowsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include "minitalk.h"

void	ft_send_bit(pid_t pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_printf("ERROR: SIGNAL COULD NOT BE SENT");
		exit(EXIT_FAILURE);
	}
}

void	ft_send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		ft_send_bit(pid, ((c >> i) & 1));
		usleep(WAIT_TIME);
		i--;
	}
}

void	ft_send_str(pid_t pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\n');
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("PROGRAM SHOULD HAVE 2 ARG!!\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("PID IS NOT VALID: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	ft_send_str(pid, argv[2]);
	return (0);
}
