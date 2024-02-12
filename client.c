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

void	ft_send_bit(pid_t pid, int bit)
{
	int	signal;

	ft_printf("read bit %d\n", bit);
	if (bit == 1)
		kill(pid, SIGUSR2);
	else if (bit == 0)
		kill(pid, SIGUSR2);
	else
	{
		ft_printf("ERROR: SIGNAL COULD NOT BE SENT");
		exit(EXIT_FAILURE);
	}
	usleep(WAIT_TIME);
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
	ft_printf("read the string %c\n", *str);
	while (*str)
	{
		ft_send_char(pid, *str++);
	}
	ft_send_char(pid, '\n');
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Program should have 2 arguments given\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	ft_printf("checked PID, str= %s\n", argv[2]);
	if (pid <= 0)
	{
		ft_printf("Not valid PID: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	ft_send_str(pid, argv[2]);
	return (0);
}
