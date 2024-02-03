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

void	ft_handler(int signo)
{
	static unsigned char		character;
	static int					bit_count;

	character = 0;
	bit_count = 0;
	if (SIGUSR1 == signo)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		ft_printf("%c", character);
		bit_count = 0;
		character = 0;
	}
	character = character << 1;
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Błąd ustawiania obsługi sygnału");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
}

int	main(void)
{
	ft_printf("PID serwera: %d\n", getpid());
	ft_signal();
	return (0);
}
