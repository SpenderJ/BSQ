/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 12:14:04 by dde-jesu          #+#    #+#             */
/*   Updated: 2017/07/26 13:57:44 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/compress.h"

void	try_change_mode(t_matrix *matrix, t_bool value)
{
	t_u8 current;

	current = matrix->lbuf->buf[(matrix->cursor / 7) - 1];
	if ((value && current == 0x7F) || (!value && current == 0x00))
	{
		matrix->lbuf->buf[(matrix->cursor / 7) - 1]
			|= ((REPEAT_MATRIX << 8) & (value << 7));
		matrix->cursor--;
	}
}

inline void	matrix_write(t_matrix *matrix, t_bool value)
{
	t_bool mode;

	if (matrix->cursor % 7 == 0)
		try_change_mode(matrix, value);
	mode = (t_bool)((matrix->lbuf->buf[matrix->cursor / 7] >> 8) & 1);
	if (mode == BINARY_MATRIX)
	{
		if (value)
			matrix->lbuf->buf[matrix->cursor / 7] |= 1 << (matrix->cursor % 7);
		matrix->cursor++;
	}
	else if (mode == REPEAT_MATRIX)
	{
		if (value != ((matrix->lbuf->buf[matrix->cursor / 7] >> 7) & 1)
			|| (matrix->lbuf->buf[matrix->cursor / 7] & 0x3F) == 0x3F)
		{
			matrix->cursor = (matrix->cursor / 7 + 1) * 7;
			matrix_write(matrix, value);
		}
		matrix->lbuf->buf[matrix->cursor / 7]++;
	}
}

void		matrix_free(t_matrix *matrix, t_u32 to)
{
	UNUSED(matrix);
	UNUSED(to);
}

void		matrix_print(t_matrix *matrix, t_info *info)
{
	UNUSED(matrix);
	UNUSED(info);
}
