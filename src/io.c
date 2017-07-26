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

inline t_reader	bsq_reader(t_u8 fd)
{
	t_reader	reader;
	ssize_t		rlen;

	BSQ_ASSERT(fd >= 0, "open failed.\n");
	BSQ_ASSERT((rlen =
		read(fd, reader.buffer, BUFF_SIZE)) != -1, "read failed.\n");
	reader.len = (t_u16)rlen;
	reader.buffer[reader.len] = '\0';
	reader.i = 0;
	reader.fd = fd;
	return (reader);
}

inline t_u8		bsq_next(t_reader *reader)
{
	t_u8	c;
	ssize_t	rlen;

	if ((c = reader->buffer[reader->i++]))
		return (c);
	BSQ_ASSERT((rlen =
		read(reader->fd, reader->buffer, BUFF_SIZE)) != -1, "read failed.\n");
	reader->len = (t_u16)rlen;
	reader->buffer[reader->len] = '\0';
	reader->i = 0;
	return reader->buffer[reader->i++];
}
