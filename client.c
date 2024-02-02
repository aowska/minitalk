#include "minitalk.h"

void ft_send_bit(int pid, int bit)
{
  int signal;

  if (bit == 1)
    signal = SIGUSR1;
  else
    signal = SIGUSR2;
  if (kill(pid, signal) == -1)
  {
    ft_printf("Error");
    exit(EXIT_FAILURE);
  }
}

void ft_send_char(int pid, unsigned char c)
{
  int i;

  i = 7;
  while (i >= 0)
  {
    ft_send_bit(pid, (c >> i) & 1); //??????????
    usleep(WAIT_TIME);
    i--;
  }
}

void ft_send_str(int pid, const char *str)
{
  while (*str)
    ft_send_char(pid, *str++);
  ft_send_char(pid, '\0');
}

int main(int argc, char **argv)
{
  pid_t pid;

  if (argc != 3)
  {
    ft_printf("Not correct input\n");
    exit(EXIT_FAILURE);
  }
  pid = ft_atoi(argv[1]);
  if (pid <= 0)
  {
    ft_printf("Invalid PID: ");
    ft_putstr_fd(argv[1], 2);
    ft_printf("\n", 2);
    exit(EXIT_FAILURE);
  }
  ft_send_str(pid, argv[2]);
  return (0);
}