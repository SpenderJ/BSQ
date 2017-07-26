/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 13:30:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/07/24 13:31:51 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <assert.h>

#include "bsq.h"

int main(void) {
	t_u8 matrix[BUFF_SIZE] = {0};

	matrix_set(matrix, 15);
	matrix_set(matrix, 48);
	matrix_set(matrix, 79);
	BSQ_ASSERT(matrix_get(matrix, 14) == FALSE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 15) == TRUE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 16) == FALSE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 47) == FALSE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 48) == TRUE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 49) == FALSE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 78) == FALSE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 79) == TRUE, "matrix error");
	BSQ_ASSERT(matrix_get(matrix, 80) == FALSE, "matrix error");
	return EXIT_SUCCESS;
}
