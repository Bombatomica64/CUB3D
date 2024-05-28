/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 10:11:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**matrixdup(char **matrix)
{
	char	**new_matrix;
	int		i;

	i = 0;
	new_matrix = malloc(sizeof(char *) * (ft_matrix_len(matrix) + 1));
	if (!new_matrix)
		return (NULL);
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}
