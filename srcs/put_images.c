/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 17:20:03 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	*put_xmp(void *mlx, char *filename, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, filename, width, height);
	if (!img)
		return (NULL);
	return (img);
}

t_img	get_img(char *path, t_game *game)
{
	t_img	img;

	img.image = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	if (!img.image)
		return (err("Failed to load texture : "), err(path), err_exit("\n", game), img);
	return (img);
}
