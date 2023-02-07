#include "window.h"

//intersec_self checks if between the light and the camera, the line intersects
//the object
int	intersect_self(t_objects *objs, t_disp_point point, int i)
{
	t_line_eq		rayline;
	t_sol_li		list;
	t_vect			rayvec;
	t_disp_point	intersection;

	init_sol_li(&list);
	rayvec = create_vector(objs->cam->position, objs->li[i].position);
	rayline = get_rayline_eq(rayvec, objs->cam->position);
	if (point.type == SP
		&& !get_specific_sphere(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == PL
		&& !get_specific_plane(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if ((point.type == CY || point.type == DI)
		&& !get_specific_cylinder(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	intersection = get_intersection(&list, objs->cam->position);
	if (list.head != NULL && list.head->solution.sol_one
		&& in_the_way(intersection.intersec_point, rayvec, objs->cam->position))
		return (free_list(&list), 0);
	return (free_list(&list), 1);
}
