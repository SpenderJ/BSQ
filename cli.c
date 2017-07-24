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

#include <stdio.h>
#include <stdalign.h>

#include "bsq.h"

int		main(int ac, char **av)
{
	printf("size: %zu, align: %zu\n", sizeof(t_square), alignof(t_square));
	printf("size: %zu, align: %zu\n", sizeof(t_map), alignof(t_map));
	printf("size: %zu, align: %zu\n", sizeof(t_bsq), alignof(t_bsq));
	return (0);
}
