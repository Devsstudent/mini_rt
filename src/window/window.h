/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:53:13 by odessein          #+#    #+#             */
/*   Updated: 2022/12/14 18:40:13 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WINDOW_H
# define WINDOW_H
# define ESC 65307
# define PI 3.1415926535
# define WIN_W 780
# define WIN_H 540
# include "minirt.h"

typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objects;
typedef void * t_mlx;

typedef struct s_mlx_info {
	t_mlx	*mlx;
	t_mlx	*win;
	t_mlx	*img;
	int		bpp;
	int		line_size;
	int		endian;
	char	*data;
}			t_mlx_info;

typedef struct s_equation {
	float	x_pow_two;
	float	x_pow_one;
	float	c;	
}				t_equation;

typedef struct s_eq{
	float	c;
	float	t;
}		t_eq;

typedef struct s_line_eq {
	t_eq	x;
	t_eq	y;
	t_eq	z;
}		t_line_eq;

//raytracing.c
t_line_eq	get_rayline_eq(t_xyz vec_line, t_xyz start_point);
t_xyz	get_vector(t_xyz hori, t_xyz verti, t_xyz orient);
t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_objects *objs);
void	loop(t_mlx_info *mlx, t_xyz hori, t_xyz verti, t_xyz start_point, t_xyz orient, t_objects *objs);
t_equation	get_quadra_plan_equation(t_line_eq rayline, t_objects *objs);

//equation.c
float	one_solu(t_equation eq);
float	first_solut(t_equation eq, float res);
float	second_solu(t_equation eq, float res);
bool	solution(t_equation eq);

//sphere_equations.c
t_xyz	get_vec_vertical(t_xyz original_pos);
t_xyz	get_vec_horizontal(t_xyz v_director, t_xyz v_ortho);
int		render_window(void	*objss);

//loop_mlx.c
int	close_window(t_mlx_info *mlx);
int	hook_press(int keycode, t_mlx_info *mlx);
int	hook_release(int keycode, t_mlx_info *mlx);
void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
bool	window(t_objects *objs);

//vector_opperation.c
t_xyz	get_orthogonal_vect(t_xyz vector);
t_xyz	get_opposite_vector(t_xyz vector);
t_xyz	vector_product(t_xyz vector_1, t_xyz vector_2);
float	norm_of_vector(t_xyz vector);
t_xyz	normalize_vector(t_xyz vector);
t_xyz	get_screen_unit_vert_vect(t_xyz unit_w, t_xyz vect_h);
t_xyz	get_screen_unit_hor_vect(t_xyz vect_d, t_xyz vect_w, int fov);
#endif
