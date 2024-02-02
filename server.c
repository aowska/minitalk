#include "minitalk.h"

// Obsługa sygnałów
void ft_handler(int signo) 
{
    static unsigned char    character;
    static int              bit_count;

    character = 0;
    bit_count = 0;
    //ft_printf("Przechwycony sygnal %d \n", signo);??????
    character = character << 1;
    if (signo == SIGUSR2)
        ;
    else if (signo == SIGUSR1)
        character = character | 1;
    //?????????????
    bit_count++;
    if (bit_count == 8)
    {
        ft_printf("%c", character);
        bit_count = 0;
        character = 0;
    }
}

void    ft_signal(void)
{
    struct sigaction    sa;

    sa.sa_handler = ft_handler;
    sa.sa_flags = SA_RESTART;
    if((sigaction(SIGUSR1, &sa, NULL)) == -1)
        ft_printf("Failed SIGUSR1");
    if((sigaction(SIGUSR2, &sa, NULL)) == -1)
        ft_printf("Failed SIGUSR2");

}

int main(void) 
{
    ft_printf("Server PID: %d \n", getpid());
    while (1) 
        ft_signal();
    return (0);
}
