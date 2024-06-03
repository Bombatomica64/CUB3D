/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:13:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

char	*itoa_base_hex(int n)
{
	char	*hex;
	char	*base;
	size_t	len;

	base = "0123456789ABCDEF";
	len = 2;
	hex = ft_calloc(sizeof(char), (len + 1));
	hex[len] = 0;
	while (len--)
	{
		hex[len] = base[n % 16];
		n /= 16;
	}
	return (hex);
}

void	color_fill(int fd)
{
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (curs.i < 99)
	{
		curs.j = 0;
		ft_putchar_fd('"', fd);
		while (curs.j < 100)
		{
			ft_putstr_fd("*", fd);
			curs.j++;
		}
		ft_putstr_fd("\",\n", fd);
		curs.i++;
	}
	curs.j = 0;
	ft_putchar_fd('"', fd);
	while (curs.j < 100)
	{
		ft_putstr_fd("*", fd);
		curs.j++;
	}
	ft_putstr_fd("\"\n};\n", fd);
}

char	*create_color_file(t_color color, t_game *game, int nm)
{
	int		fd;
	char	*hex;
	char	*path_color;

	path_color = ft_newstrjoin(ft_itoa(nm), ".xpm");
	path_color = ft_strjoin_2("assets/colors/", path_color);
	fd = open(path_color, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		err_exit("Error : Failed to create color file", game);
	ft_putstr_fd("/* XPM */\nstatic char *color[] "
		"= {\n\"100 100 1 1\",\n\"* c #", fd);
	hex = itoa_base_hex(ft_atoi(color.r));
	printf("hex = %s\n", hex);
	hex = ft_strjoin_2free(hex, itoa_base_hex(ft_atoi(color.g)));
	printf("hex = %s\n", hex);
	hex = ft_strjoin_2free(hex, itoa_base_hex(ft_atoi(color.b)));
	printf("hex = %s\n", hex);
	ft_putstr_fd(hex, fd);
	ft_putstr_fd("\",\n", fd);
	free(hex);
	color_fill(fd);
	close(fd);
	return (path_color);
}
