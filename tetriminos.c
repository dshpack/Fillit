/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:59:08 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 18:27:27 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		autofill(t_lst **node)
{
	int		i;
	int		cut_n;
	int		pohibka;
	t_lst	*current;

	i = 0;
	current = *node;
	while (i < 4)
	{
		cut_n = current->id * 21;
		current->str_coord[i] = current->str_coord[i] - cut_n;
		i++;
	}
	i = 0;
	if (current->str_coord[0] > 0)
	{
		pohibka = calc_pohibku(current);
		while (i < 4)
			current->str_coord[i++] -= pohibka;
	}
	convert_coord_to_descart(&current);
	current = NULL;
	return (0);
}

void	set_coords_to_zero(t_lst **new_node)
{
	(*new_node)->x[0] = 0;
	(*new_node)->x[1] = 0;
	(*new_node)->x[2] = 0;
	(*new_node)->x[3] = 0;
	(*new_node)->y[0] = 0;
	(*new_node)->y[1] = 0;
	(*new_node)->y[2] = 0;
	(*new_node)->y[3] = 0;
	(*new_node)->tmp_x[0] = 0;
	(*new_node)->tmp_x[1] = 0;
	(*new_node)->tmp_x[2] = 0;
	(*new_node)->tmp_x[3] = 0;
	(*new_node)->tmp_y[0] = 0;
	(*new_node)->tmp_y[1] = 0;
	(*new_node)->tmp_y[2] = 0;
	(*new_node)->tmp_y[3] = 0;
	(*new_node)->str_coord[0] = 0;
	(*new_node)->str_coord[1] = 0;
	(*new_node)->str_coord[2] = 0;
	(*new_node)->str_coord[3] = 0;
}

t_lst	*ft_make_elem(int id)
{
	t_lst	*new_node;

	if (!(new_node = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new_node->id = id;
	new_node->letter = id + 65;
	new_node->prev = NULL;
	new_node->next = NULL;
	set_coords_to_zero(&new_node);
	return (new_node);
}

t_lst	*add_node(t_lst *node, int id)
{
	t_lst	*prev;

	if (node == NULL)
	{
		node = ft_make_elem(id);
		if (!(node))
			return (NULL);
	}
	else
	{
		node->next = ft_make_elem(id);
		if (!(node->next))
			delete_listfrom_tail(&node);
		else
		{
			prev = node;
			node = node->next;
			node->prev = prev;
		}
	}
	return (node);
}

t_lst	*save_tetrimino(t_lst *head, char *buf, int len)
{
	int		i;
	int		id;
	int		j;
	int		flag;
	t_lst	*current;

	j = 0;
	id = 0;
	i = 0;
	current = NULL;
	while (buf[j] && j <= len)
	{
		flag = 0;
		if (!(current = add_node(current, id++)))
			return (NULL);
		head = (j < 21) ? current : head;
		while (flag < 5 && buf[j])
		{
			buf[j] == '\n' ? flag++ : 0;
			buf[j] == '#' ? current->str_coord[i++] = j : 0;
			j++;
		}
		i = autofill(&current);
	}
	return (head);
}
