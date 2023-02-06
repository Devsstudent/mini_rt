/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:13:47 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 21:13:34 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EDIT_H
# define EDIT_H
# include "minirt.h"

typedef float					t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz			t_xyz;
typedef struct s_objects		t_objectss;
typedef void					*t_mlx;
typedef struct s_plane			t_plane;
typedef struct s_sphere			t_sphere;
typedef struct s_edit			t_edit;
typedef enum e_type				t_type;
typedef enum e_axis				t_axis;

//action_edit.c
t_edit	get_edit(t_type type, bool *exit_request);

//edit_utils.c
char	*take_input_str(char *str);
long	get_input_nb_int(char *ask, bool *exit_request);
float	get_input_nb(char *ask, bool *exit_request);

//edit_objs.c
void	edit_objs(t_objects *objs);

//camera_edit.c
bool	ask_c(t_objects *objs);

//cylinder_edit.c
bool	ask_cy(t_objects *objs);

//plane_edit.c
bool	ask_pl(t_objects *objs);

//sphere_edit.c
bool	ask_sp(t_objects *objs);

//cones_edit.c
bool	ask_co(t_objects *objs);

//light_edit.c
bool	ask_li(t_objects *objs);

//resize.c
void	resize(t_edit *res, t_type type, bool *exit_request);

//get_rotation_angle.c
void	get_angle_rotate(t_edit *edit_info, bool *exit_request);

//rotation.c
t_vect	apply_rotation(t_vect initial, t_axis axis, int angle);
t_xyz	apply_rotation_pos(t_xyz initial, t_axis axis, int angle);

#endif
