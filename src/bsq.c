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

t_bool		bsq_solve_2nd(void *data[2], t_u32 *line, t_lbuf *root,
				t_matrix *matrix)
{
	t_u32	x;
	t_u32	lx;
	t_u8	prev;
	t_u8	c;
	t_u8	tmp;

	if ((c = bsq_next((t_reader *)data[0])) != ((t_info *)data[1])->obst
		&& c != ((t_info *)data[1])->empty)
		return (FALSE);
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
		else if (c != ((t_info *)data[1])->obst)
			return (FALSE);
		else
			line[x] = 0;
		bsq_square_check(((t_info *)data[1]), (t_u32)x, 1, line[x]);
		prev = tmp;
		lbuf_move_next(&lx, 8, &root);
	}
	return ((t_bool)(bsq_next((t_reader *)data[0]) == '\n'));
}

t_bool		bsq_solve_next(t_reader *rder, t_info *i, t_u32 *l, t_matrix *m)
{
	t_u32	y;
	t_u32	x;
	t_u32	tmp;
	t_u32	prev;
	t_u8	c;

	y = 1;
	while (++y < i->height)
	{
		if ((c = bsq_next(rder)) != i->obst && c != i->empty)
			return (FALSE);
		x = 0;
		prev = l[0];
		l[x] = matrix_write(m, (t_bool)(c == i->empty));
		while (++x < i->width)
		{
			tmp = l[x];
			if (matrix_write(m, (t_bool)((c = bsq_next(rder)) == i->empty)))
				l[x] = MIN(tmp, MIN(prev, l[x - 1])) + 1;
			else if (c != i->obst)
				return (FALSE);
			else
				l[x] = 0;
			bsq_square_check(i, x, y, l[x]);
			prev = tmp;
		}
		if (bsq_next(rder) != '\n')
			return (FALSE);
	}
	return (TRUE);
}

t_bool		bsq_solve(t_reader *reader, t_info *info)
{
	int			len;
	t_lbuf		*start;
	t_u32		*line;
	t_matrix	m;

	m = matrix();
	if ((len = bsq_read_first(reader, info, &start, &m)) == -1)
		return (FALSE);
	info->width = (t_u32)len;
	BSQ_ASSERT(line = malloc(len * sizeof(t_u32)), ALLOC_FAIL);
	if (bsq_solve_2nd((void *[2]){reader, info}, line, start, &m) == FALSE)
		return (FALSE);
	if (bsq_solve_next(reader, info, line, &m) == FALSE)
		return (FALSE);
	free(line);
	matrix_print(&m, info);
	return (TRUE);
}
