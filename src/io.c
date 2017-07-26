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

	BSQ_ASSERT(fd >= 0, IO_FAIL);
	BSQ_ASSERT((rlen = read(fd, reader.buf, BUF_SIZE)) != -1, IO_FAIL);
	reader.len = (t_u16)rlen;
	reader.buf[reader.len] = '\0';
	reader.cursor = 0;
	reader.fd = fd;
	return (reader);
}

inline t_u8		bsq_next(t_reader *reader)
{
	t_u8	c;
	ssize_t	rlen;

	if ((c = reader->buf[reader->cursor++]))
		return (c);
	BSQ_ASSERT((rlen = read(reader->fd, reader->buf, BUF_SIZE)) != -1, IO_FAIL);
	reader->len = (t_u16)rlen;
	reader->buf[reader->len] = '\0';
	reader->cursor = 0;
	return reader->buf[reader->cursor++];
}

inline void		bsq_print_at(t_bool val, t_info *info, t_u32 e)
{
	t_u32 x;
	t_u32 y;

	x = e % info->width;
	y = e / info->width;
	if (x <= info->x && y <= info->y &&
		x >= (info->x - info->m + 1) && y >= (info->y - info->m + 1))
		write(1, &info->square, 1);
	else if (val)
		write(1, &info->empty, 1);
	else
		write(1, &info->obstacle, 1);
	if (((e + 1) % info->width) == 0)
		write(1, "\n", 1);
}
