NAME = philo

FLAGS =   -I./includes #-Wall -Wextra -Werror

LIST = ./main.c

OBJ	= $(patsubst %.c,%.o,$(LIST))

all :
	@make -C ./libft/
	@make $(NAME)

$(NAME) : $(OBJ) ./libft/libft.a
	@gcc -o $(NAME) $(OBJ) ./libft/libft.a
	@echo "\033[1;32m[Success]\x1b[0m"

%.o : %.c ./includes/philo.h
	@gcc $(FLAGS) -c $< -o $@

clean :
	@make clean -C ./libft/
	@rm -f $(OBJ) $(B_OBJ)
	@echo "\033[90m[\033[33mClean\033[90m]\x1b[0m"

fclean : clean
	@make fclean -C ./libft/
	@rm -f $(NAME)
	@echo "\033[90m[\033[31mDelete\033[90m]\x1b[0m"

re : fclean all
	@echo "\033[90m[\033[35mRebuilded\033[90m]\x1b[0m"

.PHONY : all clean fclean re