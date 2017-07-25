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
	reader.i = -1;
	reader.fd = fd;
	return (reader);
}

inline t_reader	*bsq_try_read(t_reader *reader)
{
	if (reader->i >= reader->len - 1)
	{
		reader->len = (t_u16)read(reader->fd, reader->buffer, BUFF_SIZE);
		reader->i = -1;
	}
	return (reader);
}

inline t_u8		bsq_next(t_reader *reader)
{
	return bsq_try_read(reader)->buffer[++reader->i];
}

inline t_u8		bsq_peek(t_reader *reader)
{
	return (reader->buffer[reader->i]);
}
