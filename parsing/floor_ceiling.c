/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:23:12 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 12:40:13 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	validate_color_value(char *str)
{
	int			i;
	long long	value;

	i = skip_spaces2(str);
	if (ft_strlen(str + i) > 3 || ft_strlen(str + i) == 0)
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
		return (printf("here\n"), -1);
	return (value);
}

int	get_next_comma(char *path)
{
	int	i;

	i = 0;
	printf("path = |%s|\n", path);
	while (path[i] && path[i] != ',')
		i++;
	return (i);
}

void	parse_and_validate_color(t_color *color, t_game *game)
{
	color->i += get_next_comma(&(color->path[color->i]));
	if (color->color_str)
		free(color->color_str);
	color->color_str = ft_substr(color->path, color->start, color->i
			- color->start);
	color->color_value = validate_color_value(color->color_str);
	if (color->color_value == -1)
	{
		err("Invalid ");
		err(color->color_name);
		free_color(color);
		err_exit(" color value", game);
	}
	color->start = ++(color->i);
	printf("color->i = %d\n", color->i);
	printf("color->start = %d\n", color->start);
	printf("color->color_str = |%s|\n", color->color_str);
}

t_color	parse_color_values(char *path, t_game *game)
{
	t_color	color;

	color.r = NULL;
	color.g = NULL;
	color.b = NULL;
	color.path = ft_strdup(path);
	color.color_str = NULL;
	color.i = skip_spaces2(color.path);
	color.len = ft_strlen((color.path));
	color.start = color.i;
	color.color_name = "red";
	parse_and_validate_color(&color, game);
	color.r = ft_strdup(color.color_str);
	color.color_name = "green";
	parse_and_validate_color(&color, game);
	color.g = ft_strdup(color.color_str);
	color.color_name = "blue";
	parse_and_validate_color(&color, game);
	color.b = ft_strdup(color.color_str);
	return (color);
}

char	*color_rgb(char *path, t_game *game, int nm)
{
	t_color	color;

	color = parse_color_values(path, game);
	path = create_color_file(color, game, nm);
	free_color(&color);
	return (path);
}
