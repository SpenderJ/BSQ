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

	reader.len = (t_u16)read(fd, reader.buffer, BUFF_SIZE);
	reader.buffer[reader.len] = 0;
	reader.i = 0;
	reader.fd = fd;
	return (reader);
}

inline void		bsq_try_read(t_reader *reader)
{
	reader->len = (t_u16)read(reader->fd, reader->buffer, BUFF_SIZE);
	reader->buffer[reader->len] = 0;
	reader->i = 0;
}

inline t_u8		bsq_next(t_reader *reader)
{
	t_u8 c;

	if ((c = reader->buffer[reader->i++]))
		return (c);
	bsq_try_read(reader);
	return reader->buffer[reader->i++];
}
