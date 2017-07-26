/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:31:51 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/io.h"
#include "bsq/ds.h"

inline t_reader	bsq_reader(t_u8 fd)
{
	t_reader reader;
	reader.len = 0;
	reader.fd = fd;
	return (reader);
}

inline void		bsq_try_read(t_reader *reader)
{
	if (reader->len == 0)
		reader->len = (t_u16)read(reader->fd,
			(reader->cursor = reader->buffer), BUFF_SIZE);
}

inline t_u8		bsq_next(t_reader *reader)
{
	bsq_try_read(reader);
	--(reader->len);
	return *(reader->cursor++);
}
