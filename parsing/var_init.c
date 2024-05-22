/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:13:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/22 10:56:13 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_game	*init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (game);
	game->input.map_str = 0;
	init_trig(game);
	game->fov_rd = FOV * (M_PI / 180);
	game->txts.txts = ft_calloc(1, sizeof(char *));
	game->map = ft_calloc(1, sizeof(char *));
	game->txts.txt_nm = texture_names();
	print_matrix(game->txts.txt_nm);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->input.map_and_txt = parse_map(map_path, game);
	split_map(game);
	get_textures(game);
	get_texture_adresses(game);
	check_map(game);
	return (game);
}
