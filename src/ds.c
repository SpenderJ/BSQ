/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:31:51 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/ds.h"

inline void		bsq_write_binary(t_u8 *matrix, t_u32 pos, t_bool data)
{
	if (data)
		matrix[pos / 8] |= (1 << (pos % 8));
}

inline t_bool	bsq_read_binary(t_u8 *matrix, t_u32 pos)
{
	return (t_bool)((matrix[pos / 8] >> (pos % 8)) & 1);
}

inline t_bool	bsq_lbuff_next(t_u16 i, t_lbuff **buff)
{
	if (i > S_BUFF_SIZE)
	{
		BSQ_ASSERT((*buff)->next = malloc(sizeof(t_lbuff)), ALLOC_FAIL);
		*buff = (*buff)->next;
		return (TRUE);
	}
	if (*buff == NULL)
	{
		BSQ_ASSERT(*buff = malloc(sizeof(t_lbuff)), ALLOC_FAIL);
		return (TRUE);
	}
	return (FALSE);
}
