#include "window.h"
//compute cos(angle) between normal vector and rayvec
float	compute_rgb_from_angle(t_objects *objs, t_color_pam param)
{
	float	ratio;
	t_vect	rayvec;
	t_vect	normal;
	float	kd;

	if (param.disp_p.type == SP)
		normal = normalize_vector(get_normal_vect_sp(param.disp_p, objs));
	else if (param.disp_p.type == PL)
		normal = normalize_vector(get_normal_vect_pl(param.disp_p, objs));
	else if (param.disp_p.type == CY)
		normal = normalize_vector(get_normal_vect_cy(param.disp_p, objs));
	else if (param.disp_p.type == DI)
		normal = normalize_vector(get_normal_vect_di(param.disp_p, objs, 1));
	else
		return (1);
	kd = 0.7;
	rayvec = normalize_vector(param.rayvec);
	ratio = kd * fmax(scalar_product(rayvec, normal), 0);
	return (ratio);
}
