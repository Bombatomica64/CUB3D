/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:13:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 11:49:07 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

char	**texture_names(void)
{
	char	**txt_nm;

	txt_nm = malloc(sizeof(char *) * 7);
	txt_nm[0] = "NO";
	txt_nm[1] = "SO";
	txt_nm[2] = "WE";
	txt_nm[3] = "EA";
	txt_nm[4] = "SKY";
	txt_nm[5] = "FLOOR";
	txt_nm[6] = NULL;
	return (txt_nm);
}

void	get_textures(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	printf("--------------------\n");
	print_matrix(game->texture.txts);
	printf("--------------------\n");
	print_matrix(game->map);
	exit(0);
}

t_game	init_game(char *map_path)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (game);
	game.input.map_str = 0;
	game.texture.txts = ft_calloc(1, sizeof(char *));
	game.map = ft_calloc(1, sizeof(char *));
	game.texture.txt_nm = texture_names();
	print_matrix(game.texture.txt_nm);
	// game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game.input.map_and_txt = parse_map(map_path, &game);
	split_map(&game);
	get_textures(&game);
	return (game);
}
