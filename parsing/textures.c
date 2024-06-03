/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:40:19 by lmicheli         ###   ########.fr       */
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

int	validate_color_value(char *str)
{
	int			i;
	long long	value;

	i = 0;
	if (ft_strlen(str) > 3 || ft_strlen(str) == 0)
		return (-1);
	value = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	get_next_comma(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0' && path[i] != ',')
		i++;
	return (i);
}

void	color_rgb(char **path, t_game *game, int nm)
{
	int		i;
	int		len;
	int		start;
	t_color	color;

	i = skip_spaces2(*path);
	len = ft_strlen((*path));
	start = 0;
	i = get_next_comma(&(*path)[i]);
	color.r = ft_substr((*path), start, i - start);
	color.r_value = validate_color_value(color.r);
	if (color.r_value == -1)
	{
		free(color.r);
		err_exit("Invalid red color value", game);
	}
	start = ++i;
	i = get_next_comma(&(*path)[i]);
	color.g = ft_substr((*path), start, i - start);
	color.g_value = validate_color_value(color.g);
	if (color.g_value == -1)
	{
		free(color.r);
		free(color.g);
		err_exit("Invalid green color value", game);
	}
	start = ++i;
	i = len;
	color.b = ft_substr((*path), start, i - start);
	color.b_value = validate_color_value(color.b);
	if (color.b_value == -1)
	{
		free(color.r);
		free(color.g);
		free(color.b);
		err_exit("Invalid blue color value", game);
	}
	(*path) = create_color_file(color, game, nm);
	free(color.r);
	free(color.g);
	free(color.b);
}

t_img	get_floor(char *path, t_game *game, int nm)
{
	t_img	img;
	int		i;

	i = skip_spaces2(path);
	if (ft_isdigit(path[i]))
		color_rgb(&path, game, nm);
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
		if (ft_strncmp(&game->txts.txts[curs.i][curs.j], "NO ", 3) == 0)
			game->txts.imgs[0].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "SO ", 3) == 0)
			game->txts.imgs[1].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "WE ", 3) == 0)
			game->txts.imgs[2].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "EA ", 3) == 0)
			game->txts.imgs[3].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "C ", 2) == 0)
			game->txts.imgs[4].img = get_floor(game->txts.txts[curs.i] + 1,
					game, curs.i);
		else if (ft_strncmp(game->txts.txts[curs.i], "F ", 2) == 0)
			game->txts.imgs[5].img = get_floor(game->txts.txts[curs.i] + 1,
					game, curs.i);
		else if (ft_strncmp(game->txts.txts[curs.i], "DD ", 2) == 0)
			game->txts.imgs[6].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "X ", 2) == 0)
			game->txts.imgs[7].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 2, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "XL ", 3) == 0)
			game->txts.imgs[8].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 3, game);
		else if (ft_strncmp(game->txts.txts[curs.i], "XXL ", 4) == 0)
			game->txts.imgs[9].img = get_img(game->txts.txts[curs.i] + curs.j
					+ 4, game);
		else
			err_exit("Error: Invalid texture", game);
		curs.i++;
	}
}

void	get_texture_int(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		game->txts.imgs[i].data = (int *)mlx_get_data_addr(game->txts.imgs[i].img.image,
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
