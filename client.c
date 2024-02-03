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

#include "./minitalk.h"

void	ft_send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		ft_printf("Błąd wysyłania sygnału");
		exit(EXIT_FAILURE);
	}
	usleep(WAIT_TIME);
}

void	ft_send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		ft_send_bit(pid, (c >> i) & 1);
		usleep(WAIT_TIME);
	}
}

void	ft_send_str(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Nieprawidłowe wejście\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Nieprawidłowy PID: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	ft_send_str(pid, argv[2]);
	return (0);
}
