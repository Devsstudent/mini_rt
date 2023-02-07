#include "window.h"

//check_light_shadow checks if there are objects between the light and the point
t_disp_point	check_light_shadow(t_disp_point disp_p, t_objects *objs,
					int i, t_sol_li *list)
{
	t_line_eq		rayline;
	t_vect			rayvec;

	get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
	rayline = get_rayline_eq(rayvec, disp_p.intersec_point);
	if (!get_sphere(objs, list, rayline))
		return (error_intersec());
	if (!get_plane(objs, list, rayline))
		return (error_intersec());
	if (!get_cylinder(objs, list, rayline))
		return (error_intersec());
	if (!get_cones(objs, list, rayline))
		return (error_intersec());
	return (get_intersection(list, disp_p.intersec_point));
}
