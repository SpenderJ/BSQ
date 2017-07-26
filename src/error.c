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

#include "bsq/types.h"
#include "bsq/error.h"

inline void		bsq_exit(char *msg, int size)
{
	UNUSED(size = (signed)write(2, msg, (size_t)size));
	exit(1);
}
