/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:02:11 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 12:29:53 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	minimap_init(t_game *game)
{
	int	i;

	i = 0;
	game->bonus.height = (double)game->map_height * MINIMAP_SCALE;
	game->bonus.width = (double)game->map_width * MINIMAP_SCALE;
	game->bonus.minimap = ft_calloc(game->bonus.height + 1, sizeof(int *));
	while (i < game->bonus.height)
	{
		game->bonus.minimap[i] = (int *)ft_strdup(game->map[i]);
		i++;
	}
}

void	bonus_init(t_game *game)
{
	minimap_init(game);
}
