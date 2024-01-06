NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address -g3

RM = rm -rf

SRCS = 	pipex_bonus.c\
	utils_bonus.c\
	libft/libft.a\

$(NAME) :
	make all -C libft
	cc $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

bonus : clean
	make all -C libft
	cc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
