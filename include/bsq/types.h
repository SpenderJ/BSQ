/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:06:13 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 23:06:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_TYPES_H
# define FT_BSQ_TYPES_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "utils.h"

typedef unsigned int	t_uint32;
typedef unsigned char	t_uint8;

typedef struct	s_square
{
	t_uint32	dummy;
	t_uint32	x;
	t_uint32	y;
	t_uint32	m;
}				t_square;

typedef struct	s_map
{
	t_uint8		d;
	t_uint8		o;
	t_uint8		x;
	t_uint32	width;
	t_uint32	height;
}				t_map;

typedef struct	s_bsq
{
	t_square	square;
	t_map		map;
	t_uint8		in;
	t_uint8		out;
}				t_bsq;

#endif
