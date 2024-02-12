/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awacowsk <awacowsk@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:47:14 by awacowsk          #+#    #+#             */
/*   Updated: 2024/02/02 22:08:49 by awacowsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handler(int signal)
{
	static int	i;
	static int	n;
	int			nb;

	if (signal == SIGUSR1)
		nb = 0;
	else
		nb = 1;
	n = (n << 1) + nb;
	i++;
	if (i == 8)
	{
		write(1, &n, 1);
		i = 0;
		n = 0;
	}
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "\n", 1);
	while (1)
		usleep(WAIT_TIME);
}

int	main(void)
{
	ft_printf("PID serwera: %d\n", getpid());
	ft_signal();
	return (0);
}
