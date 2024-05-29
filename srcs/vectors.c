/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:55:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/29 16:57:14 by lmicheli         ###   ########.fr       */
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
