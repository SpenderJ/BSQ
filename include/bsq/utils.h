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

#ifndef FT_BSQ_UTILS_H
# define FT_BSQ_UTILS_H

# ifndef SUCCESS
#  define SUCCESS (0)
# endif

# ifndef FAILURE
#  define FAILURE (1)
# endif

# define BSQ_ASSERT(e, m) ((void)(((e)?(0):bsq_exit("Error: " m,sizeof(m)+6))))
# define ALLOC_FAIL "alloc failure"

void			bsq_exit(char *msg, int size);
unsigned int	min(unsigned int a, unsigned int b);

#endif
