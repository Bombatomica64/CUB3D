/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:13:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 17:11:08 by lmicheli         ###   ########.fr       */
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
	txt_nm[4] = "C";
	txt_nm[5] = "F";
	txt_nm[6] = NULL;
	return (txt_nm);
}

t_img	get_floor(char *path, t_game *game, int nm)
{
	t_img	img;
	t_color	color;
	int		i;

	if (ft_isdigit(path[0]))
	{
		i = 0;
		color.r = ft_substr(path, i, ft_strchr(path, ',') - path);
		i = ft_strchr(path, ',') - path + 1;
		color.g = ft_substr(path, i, ft_strchr(path + i, ',') - path - i);
		i = ft_strchr(path + i, ',') - path + 1;
		color.b = ft_substr(path, i, ft_strchr(path + i, ',') - path - i);
		path = create_color_file(color, game, nm);
	}
	img.image = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	if (!img.image)
		return (err("Failed to load texture : "), err(path), img);
	return (img);
}

void	get_textures(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	printf("--------------------\n");
	print_matrix(game->txts.txts);
	printf("--------------------\n");
	print_matrix(game->map);
	printf("--------------------\n");
	while (game->txts.txts[curs.i])
	{
		game->txts.txts[curs.i] = ft_freestrtrim(game->txts.txts[curs.i], "\n");
		printf("txts[%d] = %s\n", curs.i, game->txts.txts[curs.i]);
		curs.j = skip_spaces2(game->txts.txts[curs.i]);
		if (game->txts.txts[curs.i][curs.j] == '\0')
		{
			curs.i++;
			continue ;
		}
		if (ft_strncmp(&game->txts.txts[curs.i][curs.j], "NO", 2) == 0)
			game->txts.imgs[0] = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "SO", 2) == 0)
			game->txts.imgs[1] = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "WE", 2) == 0)
			game->txts.imgs[2] = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "EA", 2) == 0)
			game->txts.imgs[3] = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "C", 1) == 0)
			game->txts.imgs[4] = get_floor(game->txts.txts[curs.i]
					+ 4, game, curs.i);
		else if (ft_strncmp(game->txts.txts[curs.i], "F", 5) == 0)
			game->txts.imgs[5] = get_floor(game->txts.txts[curs.i]
					+ 6, game, curs.i);
		curs.i++;
	}
}

t_game	*init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (game);
	game->input.map_str = 0;
	game->fov_rd = FOV * (M_PI / 180);
	game->txts.txts = ft_calloc(1, sizeof(char *));
	game->map = ft_calloc(1, sizeof(char *));
	game->txts.txt_nm = texture_names();
	print_matrix(game->txts.txt_nm);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game->input.map_and_txt = parse_map(map_path, game);
	split_map(game);
	get_textures(game);
	check_map(game);
	return (game);
}
