/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:57 by odessein          #+#    #+#             */
/*   Updated: 2022/12/09 16:09:04 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minirt.h"
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

# define ELEM_MAX 6

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objects;

typedef struct s_must_have {
	bool	ambient;
	bool	camera;
	bool	object;
	bool	light_maj;
	bool	light;
}			t_must_have;

typedef struct s_function_parsing {
	bool	(*f)(char **, t_must_have *);
	char	*letter;
}			t_function_parsing;

//parsing.c
char	**parsing(int ac, char **av);

//utils.c
bool	check_int_max(char *str);
bool	free_split_return_false(char **line_split);
bool	ft_is_space(char c);
bool	free_array_function(t_function_parsing *arr);

//elem_struc.c
void	init_all_elem(t_must_have *all_elem);
bool	check_all_elem(t_must_have all_elem);

//split_on_function.c
char	**split_func_condition(char const *s, bool (*f)(char));

//setup_array_function.c
bool	setup_array_function(t_function_parsing **arr);

//open_and_store_content_rt.c
char	**open_and_store(char *name);

//check_ambient.c
bool	check_ambient(char **line_split, t_must_have *all_elem);

//check_camera.c
bool	check_camera(char **line_split, t_must_have *all_element);

//check_coordinate.c
bool	check_coordinate_direction(char *line);
bool	check_coordinate(char *line);

//check_cylindre.c
bool	check_cylinder(char **line_split, t_must_have *all_elem);

//check_float_construction.c
bool	check_float_construction(char *line);

//check_light.c
bool	check_light(char **line_split, t_must_have *all_element);

//check_plane.c
bool	check_plane(char **line_split, t_must_have *all_elem);

//check_rgb.c
bool	check_rgb(char *line);

//check_sphere.c
bool	check_sphere(char **line_split, t_must_have *all_elem);

//check_line_parsing.c
bool	check_line(char *line, t_function_parsing *arr, t_must_have *all_elem);

//conversions
bool	convert_to_float(float *val, char *arr);
bool	convert_to_vect_float(t_vect *val, char *arr, char *arr1, char *arr2);
bool	convert_to_rgb(t_rgb *rgb, char *arr);
bool	convert_to_xyz(t_xyz *xyz, char *arr);
bool	convert_to_orientation(t_vect *xyz, char *arr);

//fill_elems
bool	fill_ambient_light(char **arr, int j, t_objects *objects);
bool	fill_camera(char **arr, int j, t_objects *objects);
bool	fill_light(char **arr, int j, t_objects *objects);
bool	fill_sphere(char **arr, int j, t_objects *objects);
bool	fill_plane(char **arr, int j, t_objects *objects);
bool	fill_cylinder(char **arr, int j, t_objects *objects);

//build_elems
bool	build_plane(char ***triple_arr, t_objects *objects);
bool	build_cylinder(char ***triple_arr, t_objects *objects);
bool	build_sphere(char ***triple_arr, t_objects *objects);
bool	build_light(char ***triple_arr, t_objects *objects);
bool	build_camera(char ***triple_arr, t_objects *objects);
bool	build_ambient_light(char ***triple_arr, t_objects *objects);

//fill_structs
char	***create_triple_arr(char **lines);
bool	match_obj(char ***triple_arr, char *type, int i);
int		count_obj(char ***triple_arr, char *type);
bool	fill_each_struct(char ***triple_arr, t_objects *objects);
bool	fill_structs(char **lines, t_objects *objects);

#endif
