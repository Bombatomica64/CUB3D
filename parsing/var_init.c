/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:13:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/14 12:53:53 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

char	**texture_names(void)
{
	char	**txt_nm;

	txt_nm = malloc(sizeof(char *) * 5);
	if (!txt_nm)
		err("Failed to allocate texture names");
	txt_nm[0] = ft_strdup("NO");
	txt_nm[1] = ft_strdup("SO");
	txt_nm[2] = ft_strdup("WE");
	txt_nm[3] = ft_strdup("EA");
	txt_nm[4] = ft_strdup("SKY");
	txt_nm[5] = ft_strdup("FLOOR");
	return (txt_nm);
}

t_game	init_game(char *map_path)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (game);
	game.texture.txt_nm = texture_names();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game.map = parse_map(map_path, &game);
	split_map(&game);
	return (game);
}
