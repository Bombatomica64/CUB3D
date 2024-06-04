/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:34:30 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_game	*init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (NULL);
	game->input.map_str = 0;
	init_trig(game);
	game->fov_rd = FOV * M_PI / 180;
	game->txts.txt_nm = texture_names();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->input.map_and_txt = parse_map(map_path, game);
	split_map(game);
	get_textures(game);
	get_texture_int(game);
	check_map(game);
	pixels_init(game);
	game->keys = (t_keys){0, 0, 0, 0, 0, 0};
	if (BONUS)
		bonus_init(game);
	game->map[(int)game->player.pos.y][(int)game->player.pos.x] = '0';
	return (game);
}
