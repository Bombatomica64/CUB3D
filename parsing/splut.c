/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:33:08 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 16:00:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	parse_line(char *line, t_game *game)
{
	int		i;

	i = 0;
	i += skip_spaces2(line);
	if (line[i] == '\0')
		return (free(line), 0);
	if (is_in_mtx(&line[i], game->txts.txt_nm) == 1
		&& game->input.map_str == 0)
		game->txts.txts = add_to_matrix(&game->txts.txts, line);
	else if (ft_isinset(line[i], "01NSEW"))
	{
		game->map = add_to_matrix(&game->map, line);
		game->input.map_str = 1;
	}
	else
		return (free(line), -1);
	free(line);
	return (0);
}

void	split_map(t_game *game)
{
	int		size;
	int		i;
	char	*line;

	i = 0;
	size = ft_matrix_len(game->input.map_and_txt);
	while (i < size)
	{
		line = ft_strdup(game->input.map_and_txt[i]);
		if (parse_line(line, game) != -1)
			i++;
		else
			err("Failed to parse line");
	}
	ft_free_matrix(game->input.map_and_txt);
}
