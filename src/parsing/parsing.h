/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:57 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:39:52 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

# define ELEM_MAX 7

typedef struct s_must_have {
	bool	ambient;
	bool	camera;
	bool	object;
}			t_must_have;

typedef struct s_function_parsing {
	bool	(*f)(char **, t_must_have *);
	char	*letter;
}			t_function_parsing;

//utils.c
bool	free_split_return_false(char **line_split);
bool	ft_is_space(char c);
bool	free_array_function(t_function_parsing *arr);

//elem_struc.c
void	init_all_elem(t_must_have *all_elem);
bool	check_all_elem(t_must_have all_elem);

//convert_to_float.c
bool	convert_to_float(float *val, char *arr);

//split_on_function.c
char	**split_func_condition(char const *s, bool (*f)(char));

//setup_array_function.c
bool	setup_array_function(t_function_parsing *arr);

//open_and_store_content_rt.c
bool	open_and_store(char *name, char **lines);

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
bool	check_light(char **line_split);

//check_plane.c
bool	check_plane(char **line_split, t_must_have *all_elem);

//check_rgb.c
bool	check_rgb(char *line);

//check_sphere.c
bool	check_sphere(char **line_split, t_must_have *all_elem);

//chekc_line_parsing.c
bool	check_line(char *line, t_function_parsing *arr, t_must_have *all_elem);

#endif
