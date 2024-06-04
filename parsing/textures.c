/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 15:42:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

char	**texture_names(void)
{
	char	**txt_nm;

	txt_nm = ft_calloc(sizeof(char *), 11);
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
	int		i;

	i = skip_spaces2(path);
	if (ft_isdigit(path[i]))
		path = color_rgb(path, game, nm);
	img = get_img(path + skip_spaces2(path), game);
	if (!img.image)
		return (err("Error : Failed to load texture "), err(path),
			err_exit(" \n", game), img);
	free(path);
	return (img);
}

void	get_textures(t_game *game)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (game->txts.txts[curs.i])
	{
		game->txts.txts[curs.i] = ft_freestrtrim(game->txts.txts[curs.i], "\n");
		curs.j = skip_spaces2(game->txts.txts[curs.i]);
		if (game->txts.txts[curs.i][curs.j] == '\0')
		{
			curs.i++;
			continue ;
		}
		process_texture(game, &curs);
		curs.i++;
	}
}

void	get_texture_int(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (game->txts.imgs[i].img.image != NULL)
			game->txts.imgs[i].data = (int *)
				mlx_get_data_addr(game->txts.imgs[i].img.image,
					&game->txts.imgs[i].bpp, &game->txts.imgs[i].size_line,
					&game->txts.imgs[i].endian);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (game->txts.imgs[i].img.width != game->txts.imgs[i].img.height)
			err_exit("Error: texture must be square", game);
		else if (game->txts.imgs[i].img.width != TILE_SIZE)
			err_exit("Error: texture must be the correct size", game);
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
