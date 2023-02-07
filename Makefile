NAME = mini_rt
CC = cc
FLAGS = -Wall -Werror -Wextra -g -MMD
LIB = -L $(addprefix lib/, mlx) -lmlx -lXext -lX11 -lm -L $(addprefix lib/, libft) -lft
HEADER = -I $(addprefix lib/, mlx) -I $(addprefix lib/, libft) -I bonus_dir/includes -I bonus_dir/src/parsing -I bonus_dir/src/error -I bonus_dir/src/window -I bonus_dir/src/edit

OBJ = $(addsuffix .o, $(addprefix bonus_dir/obj/, main \
		$(addprefix parsing/, parsing \
							$(addprefix check_, ambient \
												camera \
												coordinate \
												cylinder \
												float_construction \
												light \
												line_parsing \
												plane \
												texture \
												rgb \
												sphere) \
								elem_structure \
								fill_objs_system_1 \
								open_and_store_content_rt \
								fill_obj_systems \
								setup_array_function \
								split_on_function \
								loop_check_coord_dir \
								conversions \
								convert_to_float \
								convert_to_vect \
								fill_structs \
								fill_cylinder \
								build_elems \
								build_light \
								fill_elems \
								utils) \
		$(addprefix error/, error \
							fill_structs_utils \
							free_objs) \
		$(addprefix window/,  loop_mlx \
								render_window \
								sphere \
								plane \
								cylinder \
								specular \
								resolve_equation \
								cylinder_equation \
								disc \
								intersection \
								raytracing_utils \
								get_normal_vector_bonus \
								vector_operations_again \
								vector_operations_bis \
								solution_list \
								raytracing \
								vector_operations \
								get_normal_vector \
								equation \
								$(addprefix color/, rgb \
										rgb_utils \
										get_pixel_color \
										shadow_light \
										check_light_shadow \
										comput_rgb_from_angle \
										intersec_self \
										$(addsuffix _color, sp \
															pl \
															cy \
															co))) \
		$(addprefix edit/, edit_objs \
								resize \
								get_rotation_angle \
								rotation \
								edit_utils \
								action_edit \
								camera_edit \
								cylinder_edit \
								sphere_edit \
								cones_edit \
								light_edit \
								plane_edit)))

BOBJ = $(addsuffix .o, $(addprefix bonus_dir/obj/, main \
		$(addprefix parsing/, parsing \
							$(addprefix check_, ambient \
												camera \
												cones_bonus \
												coordinate \
												cylinder \
												float_construction \
												light \
												line_parsing \
												plane \
												rgb \
												texture \
												sphere) \
								elem_structure \
								setup_array_function_bonus \
								open_and_store_content_rt \
								fill_obj_systems \
								split_on_function \
								loop_check_coord_dir \
								conversions \
								convert_to_float \
								convert_to_vect \
								fill_objs_system_bonus \
								fill_structs_bonus \
								fill_cones_bonus \
								fill_cone_system_bonus \
								fill_cylinder \
								build_elems \
								build_light \
								build_cones_bonus \
								fill_elems \
								utils) \
		$(addprefix error/, error \
							fill_structs_utils \
							free_objs) \
		$(addprefix window/,  loop_mlx \
								render_window \
								sphere \
								plane \
								cylinder \
								specular \
								cones_bonus \
								resolve_equation_bonus \
								get_quadra_cones_bonus \
								cylinder_equation \
								disc \
								disc_cone_bonus \
								intersection \
								raytracing_utils \
								vector_operations_again \
								solution_list \
								raytracing \
								vector_operations \
								vector_operations_bis \
								get_normal_vector \
								get_normal_vector_bonus \
								equation \
								$(addprefix color/, rgb \
										rgb_utils \
										get_pixel_color \
										shadow_light \
										check_light_shadow_bonus \
										intersec_self_bonus \
										comput_rgb_from_angle_bonus \
										$(addsuffix _color, sp \
															pl \
															cy \
															co))) \
		$(addprefix edit/, edit_objs \
								resize \
								get_rotation_angle \
								rotation \
								edit_utils \
								action_edit \
								camera_edit \
								cylinder_edit \
								sphere_edit \
								cones_edit \
								light_edit \
								plane_edit)))

ifdef TEST
	OBJ = $(BOBJ)
endif

D_LST = $(OBJ:.o=.d)

all : $(NAME)

bonus : swap 
	$(MAKE) TEST=1 all

$(NAME): $(OBJ)
	make -s -C lib/mlx
	make bonus -s -C lib/libft
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $@

BOBO =

ifdef TEST
	BOBO = -D BONUS=1
endif

bonus_dir/obj/%.o : bonus_dir/src/%.c | obj_rep
	$(CC) $(FLAGS) $(BOBO) $(HEADER) -c $< -o $@

obj_rep:
	@mkdir -p bonus_dir/obj/
	@mkdir -p bonus_dir/obj/game/
	@mkdir -p bonus_dir/obj/parsing/
	@mkdir -p bonus_dir/obj/error/
	@mkdir -p bonus_dir/obj/window/
	@mkdir -p bonus_dir/obj/edit/
	@mkdir -p bonus_dir/obj/window/color/

clean:
	make clean -s -C lib/libft
	make clean -s -C lib/mlx

swap:
	rm -rf bonus_dir/obj/window
	rm -rf bonus_dir/obj/error
	rm -rf bonus_dir/obj/parsing
fclean:
	make fclean -s -C lib/libft
	rm -f $(NAME)
	rm -rf bonus_dir/obj/

re: fclean all

.PHONY: all clean fclean re

-include $(D_LST)
