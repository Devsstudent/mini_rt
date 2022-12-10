#include "minirt.h"

t_line_eq	get_rayline_eq(t_xyz vec_line, t_xyz start_point)
{
	t_line_eq	res;

	res.x.c = start_point.x;
	res.x.t = vec_line.x;
	res.y.c = start_point.y;
	res.y.t = vec_line.y;
	res.z.c = start_point.z;
	res.z.t = vec_line.z;
	return (res);
}

t_xyz	get_vector(t_xyz hori, t_xyz verti, t_xyz orient)
{
	t_xyz	res;

	res.x = hori.x + verti.x + orient.x;
	res.y = hori.y + verti.y + orient.y;
	res.z = hori.z + verti.z + orient.z;
	return (res);
}

void loop()
{
	int	i;
	int	j;
	t_xyz	rayvec;
	t_line_eq	rayline;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			rayvec = get_vector(multp(hori, j), multp(verti, i), orient );
			rayline = get_rayline_eq(rayvec, start_point);
			//transposer dans l'equation de l'objet les x,y,z line
			j++;
		}
		i++;
	}
}
