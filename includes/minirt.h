/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:39:07 by odessein          #+#    #+#             */
/*   Updated: 2023/01/05 18:50:24 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include "mlx.h"
# include "mlx_int.h"
# include "error.h"
# include "parsing.h"
# include "libft.h"
# include "window.h"

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_mlx_info t_mlx_info;
typedef struct s_disc_info t_disc_info;

typedef struct s_xyz {
	float	x;
	float	y;
	float	z;
}		t_xyz;


typedef struct s_rgb {
	uint8_t	B; //0-255
	uint8_t	G; //0-255
	uint8_t	R; //0-255
	uint8_t	T; //0-255
}					t_rgb;

typedef union u_color {
	t_rgb	rgb;
	int	color;
}		t_color;

typedef struct s_orientation{
	float	x; //-1 1 0 20
	float	y; //-1 1
	float	z; //-1 1
}			t_orientation;

typedef struct s_ambient_light
{
	float			ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_ambient_light;

typedef struct s_camera
{
	t_xyz		position;
	t_vect		vec_direction;
	uint8_t		fov; //0-180
}				t_camera;

typedef struct s_light {
	t_xyz			position;
	float			ratio; //0 1 2 3 4 5 6 7 8 9 10
	t_rgb			color;
}					t_light;

typedef struct s_sphere {
	t_xyz		position;
	float		diameter;
	t_rgb		color;
}				t_sphere;

typedef struct	s_plane {
	t_xyz	position;
	t_vect	vec_direction;
	t_rgb	color;
}			t_plane;

typedef struct	s_cylinder {
	t_xyz			position;
	t_vect			vec_direction;
	float			diameter;
	float			height;
	t_rgb			color;
}					t_cylinder;

typedef struct s_solution {
	t_xyz	one;
	t_xyz	two;
	bool	sol_one;
	bool	sol_two;
}		t_solution;

typedef enum e_type{
	SP,
	CY,
	PL
}	t_type;

typedef struct s_solution_list {
	t_rgb					color;
	t_solution				solution;
	t_type					type;
	int						obj_id;
	struct s_solution_list	*next;
}							t_solution_list;

typedef struct s_disp_point{
	t_xyz		intersec_point;
	t_rgb		color;
	t_type		type;
	int			obj_id;
	bool		err;
}				t_disp_point;

typedef struct	s_objects {
	t_sphere		*sp;
	int			nb_sp;
	t_cylinder		*cy;
	int			nb_cy;
	t_light			*li;
	int			nb_li;
	t_plane			*pl;
	int			nb_pl;
	t_camera		*cam;
	t_ambient_light	*amb;
	t_mlx_info		*mlx;
	bool			need_display;
}	t_objects;


t_solution_list	*new_elem(t_solution solution, t_rgb color, t_type type, int i);
#endif
