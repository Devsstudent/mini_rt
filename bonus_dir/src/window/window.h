/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:53:13 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 23:09:34 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WINDOW_H
# define WINDOW_H
# define ESC 65307
# define E 101
# define WIN_W 780
# define WIN_H 540
# include "minirt.h"

typedef float						t_vect __attribute__ ((vector_size(16)));
typedef struct s_xyz				t_xyz;
typedef struct s_color_pam			t_color_pam;
typedef struct s_rgb				t_rgb;
typedef struct s_orientation		t_orientation;
typedef struct s_objects			t_objectss;
typedef void						*t_mlx;
typedef struct s_plane				t_plane;
typedef struct s_cone				t_cone;
typedef struct s_sphere				t_sphere;
typedef struct s_cylinder			t_cylinder;
typedef struct s_solution_elem		t_solution_elem;
typedef struct s_disp_point			t_disp_point;
typedef struct s_sol_li				t_sol_li;
typedef struct s_solution			t_solution;
typedef struct s_edit				t_edit;
typedef enum e_type					t_type;
typedef struct s_obj_texture		t_obj_texture;
typedef struct s_new_elem_info		t_new_elem_info;
typedef struct s_detail				t_detail;

typedef struct s_var_normal_co {
	float	xc;
	float	yc;
	float	zc;
	float	xp;
	float	yp;
	float	zp;
}			t_var_normal_co;

typedef struct s_var_normal {
	float	t;
	float	a;
	float	b;
	float	c;
}			t_var_normal;

typedef struct s_cone_variable {
	float	a;
	float	b;
	float	c;
	float	i;
	float	j;
	float	k;
	float	x0;
	float	y0;
	float	z0;
	float	xc;
	float	yc;
	float	zc;
	float	a2cos2;
	float	b2cos2;
	float	c2cos2;
	float	x0xc2;
	float	y0yc2;
	float	z0zc2;
}			t_cone_variable;

typedef struct s_final_pix_color{
	t_vect	ambient;
	t_vect	diffuse;
	t_vect	specular;
	t_vect	shadow;
}			t_final_pix_color;

typedef struct s_texture {
	t_detail	*textures;
	int			nb_textures;
	char		**paths;
}				t_texture;

typedef struct s_mlx_info {
	t_mlx		*mlx;
	t_mlx		*win;
	t_img		*img;
	int			bpp;
	int			line_size;
	int			endian;
	char		*data;
	t_texture	texture;
}				t_mlx_info;

typedef struct s_i_j{
	int	i;
	int	j;
}		t_i_j;

typedef struct s_equation {
	float	x_pow_two;
	float	x_pow_one;
	float	c;
}			t_equation;

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
}			t_eq;

typedef struct s_line_eq {
	t_eq	x;
	t_eq	y;
	t_eq	z;
}			t_line_eq;

//edit_objs.c
void			edit_objs(t_objects *objs);

//raytracing_utils.c
t_vect			multp(t_vect vector, int t);
t_line_eq		get_rayline_eq(t_vect vec_line, t_xyz start_point);
t_vect			get_vector(t_vect up_left, t_vect hori, t_vect verti);
t_vect			get_up_left(t_vect hori, t_vect verti, t_vect orient);

//sphere.c
bool			get_sphere(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool			get_specific_sphere(t_objects *obj, t_sol_li *list,
					t_line_eq rayline, int i_to_view);
t_equation		get_quadra_sphere_equation(t_line_eq rayline, t_sphere sphere);

//plane.c
bool			get_plane(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool			get_specific_plane(t_objects *obj, t_sol_li *list,
					t_line_eq rayline, int i_to_view);
t_equation		get_quadra_plan_equation(t_line_eq rayline, t_plane plane);

//cylinder.c
bool			get_cylinder(t_objects *obj, t_sol_li *list, t_line_eq rayline);
bool			get_specific_cylinder(t_objects *obj, t_sol_li *list,
					t_line_eq rayline, int i_to_view);
bool			get_disc(t_objects *obj, t_sol_li *list, t_line_eq rayline,
					int i_to_view);
bool			get_disc_cone(t_objects *obj, t_sol_li *list, t_line_eq rayline,
					int i_to_view);
t_equation		get_quadra_cylinder_equation(t_line_eq rayline,
					t_cylinder cylinder);

//get_quadra_cone_equation.c
t_equation		get_quadra_cone_equation(t_line_eq rayline, t_cone cone);

//cones.c
bool			get_specific_cone(t_objects *obj, t_sol_li *list,
					t_line_eq rayline, int i_to_view);
bool			get_cones(t_objects *obj, t_sol_li *list, t_line_eq rayline);

//raytracing_utils.c
t_line_eq		get_rayline_eq(t_vect vec_line, t_xyz start_point);

//raytracing.c
bool			loop_rendering(t_objects *objs, t_viewplan view_plan);
bool			loop_line(t_objects *objs, t_viewplan *view_plan, int i);
bool			resolve_equation(t_objects *objs, t_sol_li *list,
					t_vect rayvec, t_i_j i_j);

//intersection.c
t_disp_point	get_intersection(t_sol_li *list, t_xyz start_point);
bool			is_closer(t_xyz intersec, t_xyz start_point,
					float *final_distance);

//equation.c
bool			two_solu(t_solution *solu, t_equation eq, t_line_eq equation);
t_solution		solution(t_equation eq, t_line_eq equation, bool *error);
bool			init_solution(t_solution *solution);

//sphere_equations.c
t_vect			get_vec_vertical(t_vect original_pos);
t_vect			get_vec_horizontal(t_vect v_director, t_vect v_ortho);
int				render_window(void	*objss);

//loop_mlx.c
void			window(t_objects *objs);
void			img_pixel_put(t_mlx_info *mlx, int j, int i, int color);
int				close_window(t_objects *objs);
int				hook_press(int keycode, t_objects *objs);
int				hook_release(int keycode, t_mlx_info *mlx);
void			img_pixel_put(t_mlx_info *mlx, int j, int i, int color);

//vector_opperation.c
t_vect			create_vector(t_xyz one, t_xyz two);
t_vect			get_orthogonal_vect(t_vect vector);
t_vect			get_opposite_vector(t_vect vector);
float			norm_of_vector(t_vect vector);
float			scalar_product(t_vect one, t_vect two);
t_vect			normalize_vector(t_vect vector);
t_vect			get_screen_unit_vert_vect(t_vect unit_w, t_vect vect_h);
t_vect			get_screen_unit_hor_vect(t_vect vect_d, t_vect vect_w, int fov);

//specular.c
float			get_specular(t_vect light_vec, t_disp_point intersec,
					t_objects *objs);

//get_normal_vector.c
t_vect			get_normal_vect_cy(t_disp_point intersec, t_objects *objs);
t_vect			get_normal_vect_co(t_disp_point intersec, t_objects *objs);

//get_normal_vector_bis.c
t_vect			get_normal_vect_sp(t_disp_point intersec, t_objects *objs);
t_vect			get_normal_vect_di(t_disp_point intersec, t_objects *objs,
					bool cy);
t_vect			get_normal_vect_pl(t_disp_point intersec, t_objects *objs);

//solution_list.c
void			init_sol_li(t_sol_li *sol_li);
bool			list_add(t_sol_li *sol_li, t_solution_elem *new);
t_solution_elem	*new_elem(t_solution solution, t_new_elem_info info);
void			free_list(t_sol_li *sol_li);
void			fill_info(t_new_elem_info *info, t_rgb color, int i,
					t_obj_texture tex);

//copy_sol_two_in_one
void			copy_sol_two_in_one(t_solution *solu);

//rgb.c
void			ambient_light_quo(t_objects *objs, float RGB[3]);
void			compute_rgb(t_objects *objs, t_color_pam param,
					t_vect *diffuse, int i);
int				create_color(t_rgb rgb, t_final_pix_color final);
void			fill_specular(t_objects *objs, t_color_pam param,
					t_vect *specular, int i);
t_rgb			rgb_fill(uint8_t r, uint8_t g, uint8_t b);

//shadow_light.c
t_disp_point	check_light_shadow(t_disp_point disp_p, t_objects *objs, int i,
					t_sol_li *list);
bool			check_no_shadow(t_disp_point intersection, t_disp_point initial,
					t_objects *objs, int i);
void			get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec,
					int i);

//get_pixel_color.c
bool			get_pixel_color(int *color, t_disp_point intersec_point,
					t_objects *objs);

//co_color.c
void			cones_color(t_rgb *color, t_disp_point disp_p, t_objects *objs);

//sp_color.c
void			sphere_color(t_disp_point disp_p, t_rgb *color,
					t_objects *objs);

//pl_color.c
void			pl_color(t_rgb *color, t_disp_point disp_p, t_objects *objs);

//cy_color.c
void			cylinder_color(t_disp_point disp_p, t_objects *objs,
					t_rgb *color);

t_rgb			get_texture_color(int x, int y, t_obj_texture tex);

#endif
