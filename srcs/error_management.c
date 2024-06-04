/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 18:19:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	err(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

void	free_color(t_color *color)
{
	if (color->r)
		free(color->r);
	if (color->g)
		free(color->g);
	if (color->b)
		free(color->b);
	if (color->color_str)
		free(color->color_str);
	if (color->path)
		free(color->path);
}

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		if (game->txts.imgs[i].img.image != NULL)
			mlx_destroy_image(game->mlx, game->txts.imgs[i].img.image);
		i++;
	}
}

void	err_exit(char *msg, t_game *game)
{
	ft_putstr_fd(msg, 2);
	ft_free_matrix(game->input.map_and_txt);
	destroy_images(game);
	ft_free_matrix(game->txts.txts);
	ft_free_matrix(game->map);
	ft_free_matrix((char **)game->pixels);
	if (BONUS)
		ft_free_matrix(game->bonus.minimap);
	free(game->txts.txt_nm);
	free(game->bonus.sprite.sprite_order);
	free(game->bonus.sprite.sprite_dist);
	free(game->bonus.sprite.pos);
	if (game->bonus.frames)
		free(game->bonus.frames);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(0);
}
