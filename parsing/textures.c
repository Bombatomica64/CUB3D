/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 16:04:55 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

char	**texture_names(void)
{
	char	**txt_nm;

	txt_nm = ft_calloc(sizeof(char *), 10);
	txt_nm[0] = "NO";
	txt_nm[1] = "SO";
	txt_nm[2] = "WE";
	txt_nm[3] = "EA";
	txt_nm[4] = "C";
	txt_nm[5] = "F";
	txt_nm[6] = "DD";
	txt_nm[7] = "X";
	txt_nm[8] = "XL";
	txt_nm[9] = "XXL";
	txt_nm[10] = NULL;
	return (txt_nm);
}

t_img	get_floor(char *path, t_game *game, int nm)
{
	t_img	img;
	t_color	color;
	int		i;
	int		start;
	int		len;

	i = skip_spaces2(path);
	if (ft_isdigit(path[i]))
	{
		len = ft_strlen(path);
		printf("path = %s\n", path);
		start = 0;
		while (i < len && path[i] != ',')
			i++;
		color.r = ft_substr(path, start, i - start);
		start = ++i;
		while (i < len && path[i] != ',')
			i++;
		color.g = ft_substr(path, start, i - start);
		start = ++i;
		while (i < len && (path[i] != '\0' && path[i] != ','))
			i++;
		color.b = ft_substr(path, start, i - start);
		path = create_color_file(color, game, nm);
		free(color.r);
		free(color.g);
		free(color.b); // add free
	}
	img = get_img(path + skip_spaces2(path), game);
	if (!img.image)
		return (err("Failed to load texture : "), err(path),
			err_exit(" \n", game), img);
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
		printf("INFO:txts[%d] = %s\n", curs.i, game->txts.txts[curs.i]);
		curs.j = skip_spaces2(game->txts.txts[curs.i]);
		if (game->txts.txts[curs.i][curs.j] == '\0')
		{
			curs.i++;
			continue ;
		}
		if (ft_strncmp(&game->txts.txts[curs.i][curs.j], "NO ", 3) == 0)
			game->txts.imgs[0].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "SO ", 3) == 0)
			game->txts.imgs[1].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "WE ", 3) == 0)
			game->txts.imgs[2].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "EA ", 3) == 0)
			game->txts.imgs[3].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "C ", 2) == 0)
			game->txts.imgs[4].img = get_floor(game->txts.txts[curs.i] + 1,
					game, curs.i);
		else if (ft_strncmp(game->txts.txts[curs.i], "F ", 2) == 0)
			game->txts.imgs[5].img = get_floor(game->txts.txts[curs.i]
					+ 1, game, curs.i);
		else if (ft_strncmp(game->txts.txts[curs.i], "DD ", 2) == 0)
			game->txts.imgs[6].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "X ", 2) == 0)
			game->txts.imgs[7].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 2, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "XL ", 3) == 0)
			game->txts.imgs[8].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "XXL ", 4) == 0)
			game->txts.imgs[9].img = get_img(game->txts.txts[curs.i]
					+ curs.j + 4, game);
		else
			err_exit("Invalid texture", game);
		curs.i++;
	}
}

void	get_texture_int(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		game->txts.imgs[i].data
			= (int *)mlx_get_data_addr(game->txts.imgs[i].img.image,
				&game->txts.imgs[i].bpp, &game->txts.imgs[i].size_line,
				&game->txts.imgs[i].endian);
		i++;
	}
}

void	texture_check(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->txts.imgs[i].img.image == NULL)
			err_exit("Error: missing texture", game);
		i++;
	}
}
