/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:55:57 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 11:31:26 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H

typedef struct s_element {
	bool	ambient;
	bool	camera;
	bool	light;
	bool	plane;
	bool	sphere;
	bool	cylindre;
}			t_element;

#endif
