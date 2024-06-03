/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 16:08:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	err(char *msg)
{
	perror(msg);
	return (1);
}

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
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
	ft_free_matrix(game->bonus.sprite.sprite_order);
	ft_free_matrix(game->bonus.sprite.sprite_dist);
	ft_free_matrix(game->bonus.sprite.pos);
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
