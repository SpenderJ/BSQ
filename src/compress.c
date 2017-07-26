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
#include "bsq/io.h"

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
			= (t_u8) ((REPEAT_MATRIX << 7) | (value << 6));
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
	mode = (t_bool)((matrix->lbuf->buf[matrix->cursor / 7] >> 7) & 1);
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
			matrix->cursor = (matrix->cursor / 7 + 1) * 7;
			matrix_write(matrix, value);
		} else
			matrix->lbuf->buf[matrix->cursor / 7]++;
	}
	if (lbuf_alloca_next((t_u16)(matrix->cursor / 7), &(matrix->lbuf)))
	{
		matrix->lbuf->buf[0] = 0;
		matrix->cursor = 0;
	}
	return (value);
}

int		print_binary_matrix(t_u8 seg, t_info *info, t_u32 e)
{
	t_u8 i;
	t_u32 max;

	i = 0;
	max = (info->height * info->width) - e;
	if (max > 7)
		max = 7;
	while (i < max)
	{
		bsq_print_at((t_bool) ((seg >> ((i) % 7)) & 1), info, e + i);
		i++;
	}
	return (7);
}

int		print_repeat_matrix(t_u8 seg, t_info *info, t_u32 e)
{
	t_u8 i;
	t_bool val;
	t_u8 len;

	val = (t_bool) ((seg >> 6) & 1);
	len = (t_u8) ((seg & 0x3F) + 7);
	i = 0;
	while (i < len)
		bsq_print_at(val, info, e + i++);
	return (len);
}

void		matrix_print(t_matrix *matrix, t_info *info)
{
	t_u32 i;
	t_lbuf *lbuf;
	t_bool mode;
	t_u8 curr;
	t_u32 e;

	i = 0;
	e = 0;
	lbuf = matrix->root;
	while (e < info->height * info->width)
	{
		curr = lbuf->buf[i];
		mode = (t_bool)((curr >> 7) & 1);
		if (mode == BINARY_MATRIX)
			e += print_binary_matrix(curr, info, e);
		else if (mode == REPEAT_MATRIX)
			e += print_repeat_matrix(curr, info, e);
		lbuf_move_next(&i, 7, &lbuf);
	}
}
