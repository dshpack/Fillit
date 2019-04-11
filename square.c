/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:33:52 by kkostrub          #+#    #+#             */
/*   Updated: 2018/05/31 13:41:38 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*make_smallest_square(int len)
{
	int		i;
	int		s_n;
	int		n_pos;
	char	*c;

	i = 0;
	s_n = 1;
	while (s_n * s_n != len)
		s_n++;
	if (!(c = (char*)malloc(sizeof(char) * (len + s_n + 1))))
		return (NULL);
	c[len + s_n] = '\0';
	n_pos = s_n;
	while (i < len + s_n)
	{
		if (i != n_pos)
			c[i] = '.';
		if (i == n_pos)
		{
			c[i] = '\n';
			n_pos += s_n + 1;
		}
		i++;
	}
	return (c);
}

int		calc_smallest_square(t_lst *head, int pole_to_resize)
{
	int		id;
	int		sqr;
	t_lst	*current;

	current = head;
	while (current)
	{
		id = current->id;
		current = current->next;
	}
	id++;
	sqr = 1;
	id *= 4;
	while (sqr < id)
	{
		if (sqr * sqr < id)
			sqr++;
		if (sqr * sqr >= id)
		{
			sqr += pole_to_resize;
			sqr *= sqr;
		}
	}
	return (sqr);
}

void	rewrite_square(char **square, char c)
{
	int		i;

	i = 0;
	while ((*square)[i])
	{
		if ((*square)[i] == c)
			(*square)[i] = '.';
		i++;
	}
}

int		save_tetr_to_sqr(char **square, t_lst **node, t_coords *zdvig)
{
	int		i;
	int		pos;
	int		d_polya;

	i = 0;
	d_polya = calc_pole(*square) + 1;
	while (i < 4)
	{
		pos = (*node)->tmp_x[i] * d_polya + (*node)->tmp_y[i];
		(*square)[pos] = (*node)->letter;
		i++;
	}
	if (!(*node = (*node)->next))
		return (0);
	zdvig->zdvig_x = 0;
	zdvig->zdvig_y = 0;
	rewrite_tmp_x_y(&(*node), zdvig->zdvig_x, zdvig->zdvig_y);
	return (1);
}

int		calc_pole(char *square)
{
	int		sqr;
	int		sqrtmp;
	int		len;

	sqr = 1;
	sqrtmp = 0;
	len = (int)ft_strlen(square);
	while (sqr * sqr < len)
	{
		sqrtmp = sqr;
		sqr++;
	}
	return (sqrtmp);
}
