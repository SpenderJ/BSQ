/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:31:49 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "bsq.h"

int		main(int ac, char **av)
{
	t_reader reader;
	t_bsq_info info;

	if (ac >= 2)
		reader = bsq_reader((t_u8)open(av[1], O_RDONLY));
	else
		reader = bsq_reader(0);
	info = bsq_read_info(&reader);
	bsq_solve(&reader, &info);
	printf("%d x:%d y:%d", info.m, info.x, info.y);
	return (0);
}
