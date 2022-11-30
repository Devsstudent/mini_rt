NAME = mini_rt
CC = cc
FLAGS = -Wall -Werror -Wextra -g -MMD
LIB = -L $(addprefix lib/, mlx) -lmlx -lXext -lX11 -lm -L $(addprefix lib/, libft) -lft
HEADER = -I $(addprefix lib/, mlx) -I $(addprefix lib/, libft) -I ./includes -I ./src/parsing -I ./src/error
OBJ = $(addsuffix .o, $(addprefix obj/, main \
		$(addprefix parsing/, parsing \
							$(addprefix check_, ambient \
												camera \
												coordinate \
												cylindre \
												float_construction \
												light \
												line_parsing \
												plane \
												rgb \
												sphere) \
								convert_to_float \
								elem_structure \
								open_and_store_content_rt \
								setup_array_function \
								split_on_function \
								utils) \
		$(addprefix error/, error)))

D_LST = $(OBJ:.o=.d)

all : $(NAME)

$(NAME): $(OBJ)
	make -s -C lib/mlx
	make bonus -s -C lib/libft
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $@

obj/%.o : src/%.c | obj_rep
	$(CC) $(FLAGS) $(HEADER) -c $< -o $@

obj_rep:
	@mkdir -p obj/
	@mkdir -p obj/game/
	@mkdir -p obj/parsing/
	@mkdir -p obj/error/

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
