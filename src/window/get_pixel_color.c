#include "window.h"

static bool	loop_light(t_disp_point disp_p, t_objects *objs, float rgb[3])
{
	int					i;
	t_sol_li			list;
	t_disp_point		intersection;
	t_vect				rayvec;

	i = -1;
	while (++i < objs->nb_li)
	{
		init_sol_li(&list);
		intersection = check_light_shadow(disp_p, objs, i, &list);
		if (intersection.err)
			return (free_list(&list), false);
		if (check_no_shadow(intersection, disp_p, objs, i))
		{
			(free_list(&list));
			continue ;
		}
		get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
		compute_rgb(objs, norm_of_vector(rayvec), rgb, i);
		free_list(&list);
	}
	return (true);
}

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb	color_rgb;
	float	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	color_rgb.R = disp_p.color.R;
	color_rgb.G = disp_p.color.G;
	color_rgb.B = disp_p.color.B;
	ambient_light_quo(objs, rgb);
	loop_light(disp_p, objs, rgb);
	*color = create_color(color_rgb, rgb);
	return (true);
}
