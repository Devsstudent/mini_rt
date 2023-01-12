/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:53:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/11 15:41:16 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 
#ifndef WINDOW_H
# define WINDOW_H
# define ESC 65307
# define E 101
# define WIN_W 780
# define WIN_H 540
# include "minirt.h"

typedef float t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz			t_xyz;
typedef struct s_rgb			t_rgb;
typedef struct s_orientation	t_orientation;
typedef struct s_objects		t_objectss;
typedef void * t_mlx;
typedef struct s_plane t_plane;
typedef struct s_sphere t_sphere;
typedef struct s_cylinder t_cylinder;
typedef struct s_solution_elem	t_solution_elem;
typedef struct s_disp_point	t_disp_point;
typedef struct s_sol_li			t_sol_li;
typedef struct s_solution	t_solution;
typedef struct s_edit	t_edit;
typedef enum e_type		t_type;

typedef struct s_mlx_info {
	t_mlx	*mlx;
	t_mlx	*win;
	t_img	*img;
	int		bpp;
	int		line_size;
	int		endian;
	char	*data;
}			t_mlx_info;

typedef struct s_i_j{
	int	i;
	int	j;
}		t_i_j;

typedef struct s_equation {
	float	x_pow_two;
	float	x_pow_one;
	float	c;
}				t_equation;

typedef struct s_viewplan{
	t_vect	hori;
	t_vect	verti;
	t_vect	up_left;
}			t_viewplan;

typedef struct s_eq{
	float	c;
	float	c2;
	float	t;
	float	t2;
}		t_eq;

typedef struct s_line_eq {
	t_eq	x;
	t_eq	y;
	t_eq	z;
}		t_line_eq;

//edit_objs.c
void	edit_objs(t_objects *objs);

//raytracing_utils.c
t_vect	multp(t_vect vector, int t);
t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point);
t_vect	get_vector(t_vect up_left, t_vect hori, t_vect verti);
t_vect	get_up_left(t_vect hori, t_vect verti, t_vect orient);

//raytracing.c
bool	get_sphere(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool	get_specific_sphere(t_objects *obj, t_sol_li *list, t_line_eq rayline, int i_to_view);
bool	get_plane(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool	get_specific_plane(t_objects *obj, t_sol_li *list, t_line_eq rayline, int i_to_view);
bool	get_cylinder(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool	get_specific_cylinder(t_objects *obj, t_sol_li *list, t_line_eq rayline, int i_to_view);
bool	get_disc(t_objects *obj, t_sol_li *list, t_line_eq rayline,
		int i);
bool	loop_rendering(t_objects *objs, t_viewplan view_plan);
bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i);
t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point);
bool	resolve_equation(t_objects *objs, t_sol_li *list, t_vect rayvec, t_i_j i_j);
t_equation	get_quadra_plan_equation(t_line_eq rayline, t_plane plane);
t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_sphere sphere);
t_equation	get_quadra_cylinder_equation(t_line_eq rayline, t_cylinder cylinder);

//intersection.c
t_disp_point	get_intersection(t_sol_li *list, t_xyz start_point);
bool	is_closer(t_xyz intersec, t_xyz start_point, float *final_distance);

	//equation.c
	bool	one_solu(t_solution *solu, t_equation eq, t_line_eq equation);
	bool	two_solu(t_solution *solu, t_equation eq, t_line_eq equation);
	t_solution	solution(t_equation eq, t_line_eq equation, bool *error);
	bool	init_solution(t_solution *solution);

	//sphere_equations.c
	t_vect	get_vec_vertical(t_vect original_pos);
	t_vect	get_vec_horizontal(t_vect v_director, t_vect v_ortho);
	int		render_window(void	*objss);

	//loop_mlx.c
	void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
	int	close_window(t_objects *objs);
int	hook_press(int keycode, t_objects *objs);
	int	hook_release(int keycode, t_mlx_info *mlx);
	void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
bool	window(t_objectss *objs);

//vector_opperation.c
t_vect	create_vector(t_xyz one, t_xyz two);
t_vect	get_orthogonal_vect(t_vect vector);
t_vect	get_opposite_vector(t_vect vector);
t_vect	vector_product(t_vect vector_1, t_vect vector_2);
float	norm_of_vector(t_vect vector);
t_vect	normalize_vector(t_vect vector);
t_vect	get_screen_unit_vert_vect(t_vect unit_w, t_vect vect_h);
t_vect	get_screen_unit_hor_vect(t_vect vect_d, t_vect vect_w, int fov);

//solution_list.c
void			init_sol_li(t_sol_li *sol_li);
bool			list_add(t_sol_li *sol_li, t_solution_elem *new);
t_solution_elem	*new_elem(t_solution solution, t_rgb color, t_type type, int i);
void			free_list(t_sol_li *sol_li);

//rgb.c
void	ambient_light_quo(t_objects *objs, float RGB[3]);
int		create_color(t_rgb rgb, float RGB[3]);
void	compute_rgb(t_objects *objs, float distance, float rgb[3], int i);


//shadow_light.c
t_disp_point	check_light_shadow(t_disp_point disp_p, t_objects *objs, int i, t_sol_li *list);
bool	check_no_shadow(t_disp_point intersection, t_disp_point initial, t_objects *objs, int i);
void	get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec, int i);

//get_pixel_color.c
bool	get_pixel_color(int *color, t_disp_point intersec_point, t_objects *objs);

#endif
