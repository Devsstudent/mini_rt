#include "window.h"

char	*take_input_nb(char *str)
{
	char	*res;

	ft_putstr_fd(str, 1);
	res = get_next_line(0);
	return (res);
}

bool	check_str(char *str)
{

	if (!str)
	       return (false);
	else if (!ft_strcmp("sp", str, 3))
	       return (true);
	else if (!ft_strncmp("cy", str, 3))
	       return (true);
	else if (!ft_strncmp("pl", str, 3))
	       return (true);
	else if (!ft_strncmp("li", str, 3))
	       return (true);
	else if (!ft_strncmp("c", str, 2))
	       return (true);
	return (false);
}

void	edit_objs(t_objects *objs)
{
	long	nb;
	char	*str;
	char	*str1;

	str = 0;
	while (!check_str(str))
	{
		if (str)
			free(str);
		str = take_input_nb("Which object type you want to edit ?\n");
	}
	go_for_asked(str, objs);
}

void	go_for_asked(char *str, t_objects *objs)
{
	if (!str)
		return ;
	if (!ft_strcmp("sp", str, 3))
		ask_sp();
	if (!ft_strncmp("cy", str, 3))
		ask_cy();
	if (!ft_strncmp("pl", str, 3))
		ask_pl();
	if (!ft_strncmp("li", str, 3))
		ask_li();
	if (!ft_strncmp("c", str, 2))
		ask_c();
	free(str);
}

bool	check_edit(t_type type, char *str)
{
	if (!str)
		return (false);
	if (*str == 'r' && (type == SP || type == CY))
		return (true)
	if (*str == 'o' && (type != LI && type != SP))
		return (true);
	if (*str == 't')
		return (true);
	return (false):
}

void	get_edit(t_type type, t_objects *objs)
{
	char	*str;

	str = 0;
	while (!check_edit(type, str))
	{
		if (str)
			free(str);
		str = take_input_nb("What kind of edit you want to apply ?\nr to resize\no to rotate\nt to translate\n");
	}
	if (*str == 'r')
	{
		str = take_input_nb("new_size");
	}
	else if (*str == 'o')
	{
		//Get angle
		//Maybe the way to go clockside etc
	}
	else if (*str == 't')
	{
		//get_new_coordo
	}
}

bool	ask_sp(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;

	type = SP;
	while (nb > INT_MAX || nb > objs->nb_sp || nb <= 0)
	{
		buff = take_input_nb("Which sphere do you want to select ?\n");
		nb = atoi(buff);
		free(str);
	}
}

bool	ask_cy(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;

	type = CY;
	while (nb > INT_MAX || nb > objs->nb_cy || nb <= 0)
	{
		buff = take_input_nb("Which cylinder do you want to select ?\n");
		nb = atoi(buff);
		free(str);
	}
}

bool	ask_pl(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;

	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
	{
		buff = take_input_nb("Which plane do you want to select ?\n");
		nb = atoi(buff);
		free(str);
	}
}

bool	ask_li(t_objects *objs)
{
	t_type	type;
	long	nb;
	char	*buff;

	type = LI;
	while (nb > INT_MAX || nb > objs->nb_li || nb <= 0)
	{
		buff = take_input_nb("Which light do you want to select ?\n");
		nb = atoi(buff);
		free(str);
	}
}

bool	ask_c(t_objects *objs)
{
	t_type	type;

	type = C;
}

