CC = cc
FLAGS = -Wall -Werror -Wextra -g -MMD
LIB = -L $(addprefix ../lib/, mlx) -lmlx -lXext -lX11 -lm -L $(addprefix ../lib/, libft) -lft
HEADER = -I $(addprefix ../lib/, mlx) -I $(addprefix ../lib/, libft)
OBJ = main.o
NAME=test

D_LST = $(OBJ:.o=.d)

all : $(NAME)

$(NAME): $(OBJ)
	make -s -C ../lib/mlx
	make bonus -s -C ../lib/libft
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $@

%.o : %.c | obj_rep
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@

obj_rep:
	@mkdir -p obj/
	@mkdir -p obj/game/
	@mkdir -p obj/parsing/
	@mkdir -p obj/error/
	@mkdir -p obj/window/

clean:
	make clean -s -C lib/libft
	make clean -s -C lib/mlx

fclean: 
	make fclean -s -C lib/libft
	rm -f $(NAME)
	rm -rf obj/

re: fclean all

.PHONY: all clean fclean re

-include $(D_LST)
