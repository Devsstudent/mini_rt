# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   open_and_store_content_rt.c                        :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: odessein <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 16:23:06 by odessein          #+#    #+#              #
/*   Updated: 2022/11/28 16:24:20 by odessein         ###   ########.fr       */
#                                                                              #
# **************************************************************************** #
#include "minirt.h"

static int	line_nb(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd)
	while (line)
	{
		if (line && line[0] != '\n')
			i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (i);
}

bool	fill_lines(char **lines, int fd, int line_nb)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line && line[0] != '\n')
			lines[i++] = line;
		line = get_next_line(fd);
	}
	if (i != line_nb)
		return (false);
	return (true
}

bool	open_and_store(char *name, char **lines)
{
	int	fd;
	int	line_nber;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		return (false);
	}
	line_nber = line_nb(fd);
	lines = malloc(sizeof(*lines * (line_nber + 1)));
	close(fd);
	if (!lines)
	{
		perror("Error\n"
		return (false);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		free(lines);
		perror("Error\n");
		return (false);
	}
	if (!fill_lines(lines, fd, line_nber))
	{
		//GNL ERROR ?
		free_double_arr(lines);
		perror("Error\n");
		return (false);
	}
	close(fd);
}
