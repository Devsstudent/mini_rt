/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:37:30 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 12:46:17 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "matrix.h"

t_matrix	get_translation_matrix(float x, float y, float z)
{
	t_matrix	trans_mat;

	trans_mat[0][0] = 1;
	trans_mat[1][1] = 1;
	trans_mat[2][2] = 1;
	trans_mat[3][3] = 1;
	trans_mat[0][3] = x;
	trans_mat[1][3] = y;
	trans_mat[2][3] = z;
}
