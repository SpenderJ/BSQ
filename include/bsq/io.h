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
	t_u8	buffer[BUFF_SIZE];
	t_u16	i;
	t_u16	len;
	t_u8	fd;
}				t_reader;

t_reader		bsq_reader(t_u8 fd);
t_reader		*bsq_try_read(t_reader *reader);
t_u8			bsq_next(t_reader *reader);

#endif
