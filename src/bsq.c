/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:31:45 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void		bsq_square_check(t_bsq_info *info, t_u32 x, t_u32 y, t_u32 s)
{
	if (s > info->m)
	{
		info->x = x;
		info->y = y;
	}
}

void		bsq_solve_first(t_reader *reader, t_bsq_info *info, t_u32 *line,
				t_lbuf *first)
{
	t_u32	i;
	t_u32	j;
	t_u8	prev;

	i = 0;
	j = 0;
	prev = 0;
	while (i < info->width)
	{
		bsq_validate_char(info, bsq_peek(reader));
		if (bsq_next(reader) == info->empty)
			line[i] = min(matrix_get(first->buff, j), min(prev, line[i ? i - 1 : 0])) + 1;
		else
			line[i] = 0;
		bsq_square_check(info, (t_u32)i, 0, line[i]);
		prev = first->buff[j];
		lbuff_move_next(&j, &first);
		++i;
	}
	BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
}

void		bsq_solve_next(t_reader *reader, t_bsq_info *info, t_u32 *line)
{
	t_u32 l;
	t_i32 i;
	t_u32 tmp;
	t_u32 prev;

	l = 1;
	while (++l < info->height)
	{
		i = -1;
		prev = 0;
		while ((t_u32)++i < info->width)
		{
			bsq_validate_char(info, bsq_peek(reader));
			tmp = line[i];
			if (bsq_next(reader) == info->empty)
				line[i] = min(line[i], min(line[i ? i - 1 : 0], prev)) + 1;
			else
				line[i] = 0;
			bsq_square_check(info, (t_u32)i, l, line[i]);
			prev = tmp;
		}
		BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
	}
}

void		bsq_solve(t_reader *reader, t_bsq_info *info)
{
	t_u32	len;
	t_lbuf	*start;
	t_u32	*line;

	len = bsq_read_first(reader, info, &start);
	info->width = len;
	BSQ_ASSERT(line = malloc(len * sizeof(t_u32)), ALLOC_FAIL);
	bsq_solve_first(reader, info, line, start);
	bsq_solve_next(reader, info, line);
	free(line);
}
