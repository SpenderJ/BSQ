/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/26 17:07:35 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

inline void		bsq_square_check(t_info *info, t_u32 x, t_u32 y, t_u32 s)
{
	if (s > info->m)
	{
		info->x = x;
		info->y = y;
		info->m = s;
	}
}

void			bsq_solve_2nd(t_reader *reader, t_info *info, t_u32 *line,
							  t_lbuf *root, t_matrix *matrix)
{
	t_u32	x;
	t_u32	lx;
	t_u8	prev;
	t_u8	c;

	BSQ_ASSERT((c = bsq_next(reader)) == info->obstacle || c == info->empty,
		PARSE_ERROR);
	matrix_write(matrix, (t_bool) (c == info->empty));
	x = 0;
	lx = 0;
	prev = buf_binary_get(root->buf, lx++);
	line[x++] = (t_u32)(c == info->empty);
	while (x < info->width)
	{
		if (matrix_write(matrix, (t_bool) ((c = bsq_next(reader)) == info->empty)))
			line[x] = MIN(buf_binary_get(root->buf, lx), MIN(prev, line[x - 1])) + 1;
		else
		{
			BSQ_ASSERT(c == info->obstacle, PARSE_ERROR);
			line[x] = 0;
		}
		bsq_square_check(info, (t_u32)x, 1, line[x]);
		prev = buf_binary_get(root->buf, lx);
		lbuf_move_next(&lx, 8, &root);
		++x;
	}
	BSQ_ASSERT(bsq_next(reader) == '\n', PARSE_EXPECT("EOL"));
}

void			bsq_solve_next(t_reader *reader, t_info *info, t_u32 *line, t_matrix *matrix)
{
	t_u32	y;
	t_u32	x;
	t_u32	tmp;
	t_u32	prev;
	t_u8	c;

	y = 1;
	while (++y < info->height)
	{
		BSQ_ASSERT((c = bsq_next(reader)) == info->obstacle || c == info->empty,
			PARSE_ERROR);
		prev = line[0];
		x = 0;
		line[x] = matrix_write(matrix, (t_bool)(c == info->empty));
		while (++x < info->width)
		{
			tmp = line[x];
			if (matrix_write(matrix, (t_bool)((c = bsq_next(reader)) == info->empty)))
				line[x] = MIN(tmp, MIN(line[x - 1], prev)) + 1;
			else
			{
				BSQ_ASSERT(c == info->obstacle, PARSE_ERROR);
				line[x] = 0;
			}
			bsq_square_check(info, x, y, line[x]);
			prev = tmp;
		}
		BSQ_ASSERT(bsq_next(reader) == '\n', PARSE_EXPECT("EOL"));
	}
}

void			bsq_solve(t_reader *reader, t_info *info)
{
	t_u32	len;
	t_lbuf	*start;
	t_u32	*line;
	t_matrix m;

	m = matrix();
	len = bsq_read_first(reader, info, &start, &m);
	info->width = len;
	BSQ_ASSERT(line = malloc(len * sizeof(t_u32)), ALLOC_FAIL);
	bsq_solve_2nd(reader, info, line, start, &m);
	bsq_solve_next(reader, info, line, &m);
	free(line);
	matrix_print(&m, info);
}
