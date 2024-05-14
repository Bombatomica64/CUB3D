/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/14 12:46:06 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_spaces2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_isspace(str[i]) == TRUE)
		i++;
	return (i);
}

void	skip_spaces(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && ft_isspace(**str) == TRUE)
		(**str)++;
}

t_bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	print_matrix(char **mtx)
{
	int	i;

	i = -1;
	if (!mtx)
		return (FALSE);
	while (mtx[++i])
		printf("%s\n", mtx[i]);
	return (TRUE);
}
