/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <dde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 12:14:04 by dde-jesu          #+#    #+#             */
/*   Updated: 2017/07/26 17:40:12 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/compress.h"
#include <printf.h>


t_matrix matrix()
{
	t_matrix matrix;
	matrix.lbuf = NULL;
	lbuf_alloca_next(0, &(matrix.lbuf));
	matrix.root = matrix.lbuf;
	matrix.lbuf->buf[0] = 0;
	matrix.cursor = 0;
	return (matrix);
}

void	try_change_mode(t_matrix *matrix, t_bool value)
{
	t_u8 current;

	current = matrix->lbuf->buf[(matrix->cursor / 7) - 1];
	if ((value && current == 0x7F) || (!value && current == 0x00))
	{
		matrix->lbuf->buf[(matrix->cursor / 7) - 1]
			|= ((REPEAT_MATRIX << 8) | (value << 7));
		matrix->cursor = (matrix->cursor / 7 - 1) * 7 + 1;
	}
}

inline t_bool	matrix_write(t_matrix *matrix, t_bool value)
{
	t_bool mode;

	if (matrix->cursor % 7 == 0 && matrix->cursor > 6)
	{
		matrix->lbuf->buf[matrix->cursor / 7] = 0;
		try_change_mode(matrix, value);
	}
	mode = (t_bool)((matrix->lbuf->buf[matrix->cursor / 7] >> 8) & 1);
	if (mode == BINARY_MATRIX)
	{
		if (value)
			matrix->lbuf->buf[matrix->cursor / 7] |= 1 << (matrix->cursor % 7);
		matrix->cursor++;
	}
	else if (mode == REPEAT_MATRIX)
	{
		if (value != ((matrix->lbuf->buf[matrix->cursor / 7] >> 6) & 1)
			|| (matrix->lbuf->buf[matrix->cursor / 7] & 0x3F) == 0x3F)
		{
			matrix->cursor = (matrix->cursor / 7 + 1) * 7 + 1;
			matrix_write(matrix, value);
		}
		matrix->lbuf->buf[matrix->cursor / 7]++;
	}
	if (lbuf_alloca_next(matrix->cursor / 7, &(matrix->lbuf)))
	{
		matrix->lbuf->buf[0] = 0;
		matrix->cursor = 0;
	}
	return (value);
}

void		matrix_print(t_matrix *matrix, t_info *info)
{
	t_u32 i;
	t_lbuf *lbuf;
	t_bool mode;
	t_u8 curr;

	i = 0;
	lbuf = matrix->root;
	while (lbuf)
	{
		curr = lbuf->buf[i / 7];
		mode = (t_bool)((curr >> 8) & 1);
		if (mode == BINARY_MATRIX)
		{
			if ((curr >> (i % 7)) & 1)
				write(1, &info->empty, 1);
			else
				write(1, &info->obstacle, 1);
		}
		else if (mode == REPEAT_MATRIX)
		{
			mode = (curr >> 7) & 1;
			curr &= 0x3F;
			i = ((i / 7 + 1) * 7);
		}
		lbuf_move_next(&i, 7, &lbuf);
		if (i % info->width == 0)
			write(1, "\n", 1);
	}
}
