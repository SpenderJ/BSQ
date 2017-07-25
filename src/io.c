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

t_lbuff		*lbuff_new(char *buff, t_uint16 size)
{
	t_lbuff *node;

	if ((node = malloc(sizeof(t_lbuff))) == NULL)
		return (NULL);
	node->buff = buff;
	node->size = size;
	node->cursor = 0;
	node->prev = node;
	node->next = node;
	return (node);
}

t_lbuff		*lbuff_link(t_lbuff *node, t_lbuff *prev, t_lbuff *next)
{
	node->next = prev->next;
	node->prev = next->prev;
	prev->next = node;
	next->prev = node;
	return (node);
}

t_lbuff		*lbuff_insert_before(t_lbuff *node, char *buff, t_uint16 size)
{
	t_lbuff *n;

	if ((n = lbuff_new(buff, size)) == NULL)
		return (NULL);
	return (lbuff_link(n, node->prev, node));
}

t_lbuff		*lbuff_push(t_lbuff *self, char *buff, t_uint16 size)
{
	return (lbuff_insert_before(self, buff, size));
}

char		*bsq_read_infoline(int fd, t_uint32 *size, t_lbuff *root)
{
	char		buff[BUFF_SIZE];
	char		*pbuff;
	short		readsize;

	if ((readsize = (t_uint16)read(fd, buff, BUFF_SIZE)) == -1)
		return (NULL);
	while (*size < readsize && buff[*size] != '\n')
		if (buff[(*size)++] == '\0')
			return (NULL);
	if (*size >= readsize ||
		(pbuff = malloc(sizeof(char) * (*size + 1))) == (NULL))
		return (NULL);
	root->size = (t_uint16)(readsize - *size);
	if ((root->buff = malloc(sizeof(char) * (root->size + 1))) == NULL)
		return (NULL);
	fd = -1;
	while (++fd < *size)
		pbuff[fd] = buff[fd];
	if (buff[fd] != '\n')
		return (NULL);
	pbuff[fd] = '\0';
	while (++fd < readsize)
		root->buff[fd - *size - 1] = buff[fd];
	root->buff[fd - *size - 1] = '\0';
	return (pbuff);
}

t_uint32	*bsq_read_firstline(int fd, t_uint32 *size)
{
	return (NULL);
}

t_uint32	*bsq_read_line(int fd, t_uint32 *size)
{
	return (NULL);
}

char		*bsq_getline(t_bsq *bsq, t_uint32 *size)
{
	return (NULL);
}

char		*bsq_fgetline(t_bsq *bsq, t_uint32 size)
{
	return (NULL);
}
