/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/25 04:51:15 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/matrix.h"

static t_uint32		matrix_3(t_uint32 *old, t_uint32 *new, t_uint32 i)
{
	if (new[i - 1] == old[i] && old[i] == old[i - 1])
		return (old[i]);
	if (new[i - 1] >= old[i] && old[i - 1] >= old[i])
		return (old[i]);
	if (old[i - 1] >= new[i] && old[i] >= new[i])
		return (new[i]);
	return (old[i - 1]);
}

int					bsq_eval(t_bsq *bsq, t_uint32 *old, t_uint32 *new)
{
	int	i;

	i = -1;
	while (++i < bsq->map.width)
	{
		if (i > 0 && new[i] != 0)
			new[i] = new[i] + matrix_3(old, new, i);
		else if (new[i] != 0)
			new[i] = new[i] + old[i];
		if (new[i] > bsq->square.m && (bsq->square.m = new[i]))
		{
			bsq->square.x = i;
			bsq->square.y = bsq->square.dummy;
		}
	}
	return (SUCCESS);
}
