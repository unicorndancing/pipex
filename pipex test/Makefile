
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
NAME = pipextruc
OBJS = $(SRCS:.c=.o)

SRCS = 	pipex.c \
		pipex2.c
		
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
	$(CC) -o pipex $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
