/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:26:33 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 10:17:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**rem_from_matrix(char **matrix, int index)
{
	char	**new_matrix;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_matrix = malloc(sizeof(char *) * (ft_matrix_len(matrix)));
	if (!new_matrix)
		return (NULL);
	while (matrix[i])
	{
		if (i != index)
		{
			new_matrix[j] = ft_strdup(matrix[i]);
			j++;
		}
		i++;
	}
	new_matrix[j] = NULL;
	ft_free_matrix(matrix);
	return (new_matrix);
}

char	**add_to_matrix(char **matrix, char *line)
{
	char	**new_matrix;
	int		i;

	i = 0;
	new_matrix = ft_calloc(sizeof(char *), (ft_matrix_len(*matrix) + 2));
	if (!new_matrix)
		return (NULL);
	if (ft_matrix_len(*matrix) == 0)
	{
		new_matrix[0] = ft_strdup(line);
		new_matrix[1] = NULL;
		return (new_matrix);
	}
	while ((*matrix)[i])
	{
		new_matrix[i] = ft_strdup((*matrix)[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(line);
	new_matrix[i + 1] = NULL;
	ft_free_matrix(*matrix);
	return (new_matrix);
}

int	is_in_mtx(char *line, char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (-1);
	while (matrix[i])
	{
		if (ft_strncmp(line, matrix[i], ft_strlen(matrix[i])) == 0)
			return (1);
		i++;
	}
	return (-1);
}
