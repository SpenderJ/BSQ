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

void	try_change_mode(t_bsq_matrix *matrix, t_bool value)
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

void	bsq_matrix_write(t_bsq_matrix *matrix, t_bool value)
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
			bsq_matrix_write(matrix, value);
		}
		matrix->lbuf->buf[matrix->cursor / 7]++;
	}
}

void	bsq_matrix_free(t_bsq_matrix *matrix, t_u32 to)
{
	UNUSED(matrix);
	UNUSED(to);
}

void	bsq_matrix_print(t_bsq_matrix *matrix, t_bsq_info *info)
{
	UNUSED(matrix);
	UNUSED(info);
}
