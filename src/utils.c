/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:30:23 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/utils.h"
#include "bsq/types.h"

inline void		bsq_exit(char *msg, int size)
{
	write(2, msg, (size_t)size);
	exit(1);
}

inline t_u32	min(t_u32 a, t_u32 b)
{
	return (a < b ? a : b);
}
