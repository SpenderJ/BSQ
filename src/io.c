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

#include <tclDecls.h>
#include "bsq/io.h"
#include "bsq/parser.h"

t_lbuff		*lbuff_new(t_uint32 *buff, t_uint16 size)
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

t_lbuff		*lbuff_insert_before(t_lbuff *node, t_uint32 *buff, t_uint16 size)
{
	t_lbuff *n;

	if ((n = lbuff_new(buff, size)) == NULL)
		return (NULL);
	return (lbuff_link(n, node->prev, node));
}

t_lbuff		*lbuff_push(t_lbuff *self, t_uint32 *buff, t_uint16 size)
{
	return (lbuff_insert_before(self, buff, size));
}

int			bsq_read_infoline(t_bsq *bsq, t_lbuff *root)
{
	char		buff[BUFF_SIZE];
	short		readsize;
	t_uint32	size;
	short		i;
	t_map		map;

	size = 0;
	if ((readsize = (t_uint16)read(bsq->in, buff, BUFF_SIZE)) == -1)
		return (FAILURE);
	while (size < readsize && buff[size] != '\n')
		if (buff[size++] == '\0')
			return (FAILURE);
	root->size = (t_uint16)(readsize - size);
	if (size >= readsize || buff[i = (short)(size)] != '\n' ||
		bsq_parse_map(&map, buff, size) == FAILURE ||
		(root->buff = malloc(sizeof(t_uint32) * (root->size + 1))) == NULL)
		return (FAILURE);
	while (++i < readsize)
		if (buff[i] == '\n')
			root = lbuff_push(root, root->buff + i + 1, readsize - i - 1);
		root->buff[i - size - 1] = buff[i] == map.d ? 1 : 0;
	root->buff[i - size] = '\0';
}

t_uint32	*bsq_read_firstline(t_bsq *bsq, t_lbuff *root)
{
	return (NULL);
}

t_uint32	*bsq_read_line(t_bsq *bsq, t_uint32 *size)
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
