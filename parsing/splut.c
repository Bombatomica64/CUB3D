/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:33:08 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/14 13:00:30 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	parse_line(char *line, t_game *game)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	i += skip_spaces2(line);
	if (line[i] == '\0')
		return ;
	if (is_in_mtx(line[i], game->texture.txt_nm))
	{
		add_to_matrix(game->texture.txts, line);
	}
	// if (ft_isinset(line[i], "012NSEW"))
	// 	add_to_matrix(game->map, line);
	//matrix_utils.c
}

void	split_map(t_game *game)
{
	int		size;
	int		i;
	char	*line;
	char	**map;

	i = 0;
	size = ft_matrix_len(game->map);
	while (i < size)
	{
		line = ft_strdup(game->map[i]);
		parse_line(line, game);
	}

}
