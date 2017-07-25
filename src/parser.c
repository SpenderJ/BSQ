/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 00:16:08 by juspende          #+#    #+#             */
/*   Updated: 2017/07/25 02:22:28 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/parser.h"

inline void			bsq_validate_char(t_bsq_info *info, char c)
{
	BSQ_ASSERT(c == info->obstacle || c == info->empty, "Bad char in map");
}

inline void			bsq_validate_info(t_bsq_info *info)
{
	BSQ_ASSERT(info->height > 0,
		"height is invalid\n");
	BSQ_ASSERT(info->empty != 0,
		"empty marker is missing\n");
	BSQ_ASSERT(info->obstacle != 0,
		"obstacle marker is missing\n");
	BSQ_ASSERT(info->square != 0,
		"square marker is missing\n");
	BSQ_ASSERT(info->square != info->obstacle,
		"Two markers have same identity\n");
	BSQ_ASSERT(info->square != info->empty,
		"Two markers have same identity\n");
}

inline t_bsq_info	bsq_read_info(t_reader *reader)
{
	t_bsq_info	info;
	t_u8		buff[13];
	t_u8		i;
	t_u8		j;

	i = 0;
	while (bsq_peek(reader) != '\n' && i < 13)
		buff[i++] = bsq_next(reader);
	info.square = buff[--i];
	info.obstacle = buff[--i];
	info.empty = buff[--i];
	info.x = 0;
	info.y = 0;
	info.m = 0;
	j = 0;
	info.height = 0;
	while (buff[j] && buff[j] >= '0' && buff[j] <= '9' && j < i)
		info.height = info.height * 10 + (buff[j++] - '0');
	BSQ_ASSERT(i == j, "wrong format -42\n");
	BSQ_ASSERT(bsq_next(reader) == '\n', "wrong format -42\n");
	bsq_validate_info(&info);
	return (info);
}

inline t_u32		bsq_read_first(t_reader *reader, t_bsq_info *info,
						t_lbuf **first)
{
	t_lbuf	*buff;
	t_u16	i;
	t_u32	len;

	buff = NULL;
	i = 0;
	lbuff_alloca_next(i, &buff);
	*first = buff;
	len = 0;
	while (bsq_peek(reader) != '\n')
	{
		bsq_validate_char(info, bsq_peek(reader));
		if (lbuff_alloca_next((t_u16) (i / 8), &buff))
			i = 0;
		matrix_set(buff->buff, i, (t_bool) (bsq_next(reader) == info->empty));
		i++;
		len++;
	}
	BSQ_ASSERT(bsq_next(reader) == '\n', "Expected EOL");
	return (len);
}
