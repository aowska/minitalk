NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./Libft/libft.a
RM = rm -rf

SERVER = server
CLIENT = client

SERVER_SRCS = server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_SRCS = client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C ./Libft

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) -o server

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) -o client
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./Libft
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(MAKE) fclean -C ./Libft
	$(RM) $(SERVER) $(CLIENT)
	
re: fclean all 

.PHONY: all check show clean