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
#include "bsq/io.h"
#include "bsq/matrix.h"
#include "bsq/utils.h"

static t_uint32	ft_atoi(const char *str)
{
	t_uint32	val;

	val = 0;
	while (*str && *str >= '0' && *str <= '9')
		val = val * 10 + (*str++ - 48);
	return (val);
}

int				bsq_parse_map(t_map *map, char *new, t_uint32 size)
{
	if (size < 4)
		return (FAILURE);
	map->x = (t_uint8)new[size - 1];
	map->o = (t_uint8)new[size - 2];
	map->d = (t_uint8)new[size - 3];
	new[size - 3] = '\0';
	if ((map->height = ft_atoi(new)) == 0)
		return (FAILURE);
	return (SUCCESS);
}

static int		check_line(t_bsq *bsq, char *str, t_uint32 size)
{
	t_uint32	count;

	count = 0;
	if (size <= 0 || str == NULL)
		return (FAILURE);
	while (*str && ++count && (*str == bsq->map.x || *str == bsq->map.o ||
			*str == bsq->map.d))
		;
	if (count != size || *str != '\0')
		return (FAILURE);
	return (SUCCESS);
}

int				bsq_parse(t_bsq *bsq, int fd)
{
	t_uint32		c;
	t_uint32		size;
	char			*new;
	char			*old;

	c = 0;
	bsq->in = (t_uint8)fd;
	while ((new = bsq_getline(bsq, &size)) != NULL && c <= 1)
	{
		if (c == 0 && (bsq_parse_map(bsq, new, size)) == FAILURE)
			return (FAILURE);
		else if (c == 1 && (bsq->map.width = size) &&
				(check_line(bsq, new, bsq->map.width)) == FAILURE)
			return (FAILURE);
		++c;
	}
	while ((old = new) != NULL && c++)
		if ((new = bsq_fgetline(bsq, size)) == NULL)
			break ;
		else if ((check_line(bsq, new, bsq->map.width) == FAILURE) ||
				(bsq_eval(bsq, old, new) == FAILURE))
			return (FAILURE);
	if (c != bsq->map.height)
		return (FAILURE);
	return (SUCCESS);
}
