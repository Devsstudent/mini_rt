/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:13:47 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 16:20:17 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EDIT_H
# define EDIT_H
# include "minirt.h"

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objectss;
typedef void * t_mlx;
typedef struct s_plane t_plane;
typedef struct s_sphere t_sphere;
typedef struct s_solution_list	t_solution_list;
typedef struct s_disp_point	t_disp_point;
typedef struct s_solution	t_solution;
typedef struct s_edit	t_edit;
typedef enum e_type		t_type;
typedef enum e_axis		t_axis;

//action_edit.c
t_edit	get_edit(t_type type);

//edit_utils.c
char	*take_input_str(char *str);
long	get_input_nb(char *ask);

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

//light_edit.c
bool	ask_li(t_objects *objs);

//rotation.c
t_vect	apply_rotation(t_vect initial, t_axis axis, int angle);
t_xyz	apply_rotation_pos(t_xyz initial, t_axis axis, int angle);

#endif
