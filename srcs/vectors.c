/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:55:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:30:45 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_pos	add(t_pos a, t_pos b)
{
	t_pos	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_pos	sub(t_pos a, t_pos b)
{
	t_pos	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_pos	mult(t_pos a, double b)
{
	t_pos	res;

	res.x = a.x * b;
	res.y = a.y * b;
	return (res);
}

t_pos	scale(t_pos a, double b)
{
	t_pos	res;

	res.x = a.x * b;
	res.y = a.y * b;
	return (res);
}

t_pos	rot(t_pos pos, double angle)
{
	t_pos	new_pos;

	new_pos.x = pos.x * cos(angle) - pos.y * sin(angle);
	new_pos.y = pos.x * sin(angle) + pos.y * cos(angle);
	return (new_pos);
}
