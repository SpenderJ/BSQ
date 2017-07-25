/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:05:56 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/25 00:17:20 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_PARSER_H
# define FT_BSQ_PARSER_H

# include "types.h"

int		bsq_parse(t_bsq *bsq, int fd);
int		bsq_parse_map(t_map *map, char *new, t_uint32 size);

#endif
