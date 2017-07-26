/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:05:36 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 23:05:37 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_IO_H
# define FT_BSQ_IO_H

# include "types.h"

typedef struct	s_reader
{
	t_u8	buf[BUF_SIZE + 1];
	t_u16	cursor;
	t_u16	len;
	t_u8	fd;
}				t_reader;

extern t_reader	bsq_reader(t_u8 fd);
extern t_u8		bsq_next(t_reader *reader);
extern void		bsq_print_at(t_bool val, t_info *info, t_u32 e);

#endif
