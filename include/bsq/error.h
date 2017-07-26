/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 23:06:42 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 23:06:43 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_ERROR_H
# define FT_BSQ_ERROR_H

# define BSQ_ASSERT(e, m) ((void)(((e)?(0):bsq_exit(m,sizeof(m)-1))))

# ifdef STANDARD_ERRORS
#  define MAP_ERROR "map error\n"
#  define PARSE_ERROR MAP_ERROR
#  define PARSE_EXPECT MAP_ERROR
#  define ALLOC_FAIL "\n"
# else
#  define PARSE_ERROR "Error: Unexpected char found in the proceeded map.\n"
#  define PARSE_EXPECT "Error: Unexpected char found int the proceeded map.\n"
#  define ALLOC_FAIL "Error: Allocation failure.\n"
# endif

void	bsq_exit(char *msg, int size);

#endif
