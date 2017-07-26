/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:05:22 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/25 00:17:01 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_H
# define FT_BSQ_H

# include "bsq/ds.h"
# include "bsq/io.h"
# include "bsq/parser.h"
# include "bsq/types.h"
# include "bsq/utils.h"

extern void	bsq_square_check(t_info *info, t_u32 x, t_u32 y, t_u32 s);
void		bsq_solve(t_reader *reader, t_info *info);

#endif
