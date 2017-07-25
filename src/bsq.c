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

inline void	bsq_validate_char(t_bsq_info *info, char c)
{
	BSQ_ASSERT(c == info->obstacle || c == info->empty, "Bad char in map");
}

t_u32		bsq_solve_first(t_reader *reader, t_bsq_info *info, t_lbuff **start)
{
	t_lbuff	*buff;
	t_u16	i;
	t_u32	len;

	buff = NULL;
	i = 0;
	bsq_lbuff_next(i, &buff);
	*start = buff;
	len = 0;
	while (bsq_peek(reader) != '\n')
	{
		bsq_validate_char(info, bsq_peek(reader));
		if (bsq_lbuff_next((t_u16)(i / 8), &buff))
			i = 0;
		bsq_write_binary(buff->buff, i, (t_bool) (bsq_next(reader) == info->empty));
		i++;
		len++;
	}
	BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
	return (len);
}

void		bsq_solve_2nd(t_reader *reader, t_bsq_info *info, t_u32 *line,
			t_lbuff *first)
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
			line[i] = min(first->buff[j], min(prev, line[i ? i - 1 : 0])) + 1;
		else
			line[i] = 0;
		prev = first->buff[j];
		i++;
		j++;
		if (j > S_BUFF_SIZE)
		{
			first = first->next;
			j = 0;
		}
	}
	BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
}

void		bsq_solve_next(t_reader *reader, t_bsq_info *info, t_u32 *line)
{
	t_u32 l;
	t_u32 i;
	t_u32 tmp;
	t_u32 prev;

	l = 2;
	while (l < info->height)
	{
		i = 0;
		prev = 0;
		while (i < info->width)
		{
			bsq_validate_char(info, bsq_peek(reader));
			tmp = line[i];
			if (bsq_next(reader) == info->empty)
				line[i] = min(line[i], min(line[i ? i - 1 : 0], prev)) + 1;
			else
				line[i] = 0;
			prev = tmp;
			i++;
		}
		BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
		l++;
	}
}

void		bsq_solve(t_reader *reader, t_bsq_info *info)
{
	t_u32	len;
	t_lbuff	*start;
	t_u32	*line;

	len = bsq_solve_first(reader, info, &start);
	info->width = len;
	BSQ_ASSERT(line = malloc(len * sizeof(t_u32)), ALLOC_FAIL);
	bsq_solve_2nd(reader, info, line, start);
	bsq_solve_next(reader, info, line);
}
