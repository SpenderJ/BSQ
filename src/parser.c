/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 00:16:08 by juspende          #+#    #+#             */
/*   Updated: 2017/07/26 16:37:49 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/parser.h"
#include "bsq.h"

inline void		bsq_validate_info(t_info *info)
{
	BSQ_ASSERT(info->height > 0, PARSE_ERR);
	BSQ_ASSERT(info->empty != 0, PARSE_ERR);
	BSQ_ASSERT(info->obst != 0, PARSE_ERR);
	BSQ_ASSERT(info->square != 0, PARSE_ERR);
	BSQ_ASSERT(info->square != info->obst, PARSE_ERR);
	BSQ_ASSERT(info->square != info->empty, PARSE_ERR);
}

inline t_info	bsq_read_info(t_reader *reader)
{
	t_info	info;
	t_u8	buff[13];
	t_u8	i;
	t_u8	j;
	t_u8	c;

	i = 0;
	while ((c = bsq_next(reader)) != '\n' && i < 13)
		buff[i++] = c;
	info.square = buff[--i];
	info.obst = buff[--i];
	info.empty = buff[--i];
	info.x = 0;
	info.y = 0;
	info.m = 0;
	j = 0;
	info.height = 0;
	while (buff[j] && buff[j] >= '0' && buff[j] <= '9' && j < i)
		info.height = info.height * 10 + (buff[j++] - '0');
	BSQ_ASSERT(i == j, PARSE_ERR);
	BSQ_ASSERT(c == '\n', PARSE_ERR);
	bsq_validate_info(&info);
	return (info);
}

inline t_u32	bsq_read_first(t_reader *reader, t_info *info, t_lbuf **first,
					t_matrix *matrix)
{
	t_lbuf	*buff;
	t_u16	lx;
	int		len;
	t_u8	c;

	buff = NULL;
	lx = 0;
	lbuf_alloca_next(lx, &buff);
	*first = buff;
	len = -1;
	while (++len >= 0 && (c = bsq_next(reader)) != '\n')
	{
		if (lbuf_alloca_next((t_u16)(lx / 8), &buff))
			lx = 0;
		if (matrix_write(matrix, (t_bool)(c == info->empty)))
		{
			buf_binary_set(buff->buf, lx);
			bsq_square_check(info, (t_u32)len, 0, 1);
		}
		else
			BSQ_ASSERT(c == info->obst, PARSE_ERR);
		lx++;
	}
	BSQ_ASSERT(c == '\n', PARSE_EXPECT("EOL"));
	return ((t_u32)len);
}
