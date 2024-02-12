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
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

#include "minitalk.h"
#include <sys/types.h>

void	ft_handler(int signo)
{
	static unsigned char		character = 0;
	static int					bit_count = 0;

	character = character << 1;
	if (signo == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%c", character);
		bit_count = 0;
		character = 0;
	}
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("ERROR: FAILD SIGNAL TO HENDLER\n", 2);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	ft_signal();
	return (0);
}
