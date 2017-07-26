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

inline void	bsq_square_check(t_info *info, t_u32 x, t_u32 y, t_u32 s)
{
	if (s > info->m)
	{
		info->x = x;
		info->y = y;
		info->m = s;
	}
}

void		bsq_solve_2nd(void *data[2], t_u32 *line, t_lbuf *root,
				t_matrix *matrix)
{
	t_u32	x;
	t_u32	lx;
	t_u8	prev;
	t_u8	c;
	t_u8	tmp;

	BSQ_ASSERT((c = bsq_next((t_reader *)data[0])) == ((t_info *)data[1])->obst
		|| c == ((t_info *)data[1])->empty, PARSE_ERR);
	x = 0;
	lx = 0;
	prev = buf_binary_get(root->buf, lx++);
	line[x] = matrix_write(matrix, (t_bool)(c == ((t_info *)data[1])->empty));
	while (++x < ((t_info *)data[1])->width)
	{
		tmp = buf_binary_get(root->buf, lx);
		if (matrix_write(matrix, (t_bool)((c = bsq_next((t_reader *)data[0]))
			== ((t_info *)data[1])->empty)))
			line[x] = MIN(tmp, MIN(prev, line[x - 1])) + 1;
		else
			line[x] = BSQ_ASSERT(c == ((t_info *)data[1])->obst, PARSE_ERR);
		bsq_square_check(((t_info *)data[1]), (t_u32)x, 1, line[x]);
		prev = tmp;
		lbuf_move_next(&lx, 8, &root);
	}
	BSQ_ASSERT(bsq_next((t_reader *)data[0]) == '\n', PARSE_EXPECT("EOL"));
}

void		bsq_solve_next(t_reader *rder, t_info *i, t_u32 *l, t_matrix *m)
{
	t_u32	y;
	t_u32	x;
	t_u32	tmp;
	t_u32	prev;
	t_u8	c;

	y = 1;
	while (++y < i->height)
	{
		BSQ_ASSERT((c = bsq_next(rder)) == i->obst || c == i->empty, PARSE_ERR);
		x = 0;
		prev = l[0];
		l[x] = matrix_write(m, (t_bool)(c == i->empty));
		while (++x < i->width)
		{
			tmp = l[x];
			if (matrix_write(m, (t_bool)((c = bsq_next(rder)) == i->empty)))
				l[x] = MIN(tmp, MIN(prev, l[x - 1])) + 1;
			else
				l[x] = BSQ_ASSERT(c == i->obst, PARSE_ERR);
			bsq_square_check(i, x, y, l[x]);
			prev = tmp;
		}
		BSQ_ASSERT(bsq_next(rder) == '\n', PARSE_EXPECT("EOL"));
	}
}

void		bsq_solve(t_reader *reader, t_info *info)
{
	t_u32		len;
	t_lbuf		*start;
	t_u32		*line;
	t_matrix	m;

	m = matrix();
	len = bsq_read_first(reader, info, &start, &m);
	info->width = len;
	BSQ_ASSERT(line = malloc(len * sizeof(t_u32)), ALLOC_FAIL);
	bsq_solve_2nd((void *[2]){reader, info}, line, start, &m);
	bsq_solve_next(reader, info, line, &m);
	free(line);
	matrix_print(&m, info);
}
