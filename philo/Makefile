NAME = philo

FLAGS =   -I./includes -Wall -Wextra -Werror

LIST = ./src/main.c ./src/utils.c ./src/time.c ./src/set_info.c ./src/simulation.c

OBJ	= $(patsubst %.c,%.o,$(LIST))

all :
	@make $(NAME)

$(NAME) : $(OBJ)
	@gcc -o $(NAME) $(OBJ)
	@echo "\033[1;32m[Success]\x1b[0m"

%.o : %.c includes
	@gcc $(FLAGS) -c $< -o $@

clean :
	@rm -f $(OBJ) $(B_OBJ)
	@echo "\033[90m[\033[33mClean\033[90m]\x1b[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[90m[\033[31mDelete\033[90m]\x1b[0m"

re : fclean all
	@echo "\033[90m[\033[35mRebuilded\033[90m]\x1b[0m"

.PHONY : all clean fclean re