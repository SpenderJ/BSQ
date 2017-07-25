/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:05:36 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 23:05:37 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_DS_H
# define BSQ_DS_H

# include "types.h"

# define S_BUFF_SIZE (BUFF_SIZE - sizeof(struct s_lbuff*))

void			matrix_set(t_u8 *matrix, t_u32 pos, t_bool data);
t_bool			matrix_get(t_u8 *matrix, t_u32 pos);


typedef	struct	s_lbuff
{
	t_u8			buff[S_BUFF_SIZE];
	struct s_lbuff	*next;
}				t_lbuf;

t_bool			lbuff_alloca_next(t_u16 i, t_lbuf **buff);
void			lbuff_move_next(t_u32 *i, t_lbuf **buff);

#endif
