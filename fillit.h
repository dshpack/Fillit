/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:12:28 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 17:23:29 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# define BUF_SIZE 546
# include "libft/libft.h"

typedef struct			s_coords
{
	int					zdvig_x;
	int					zdvig_y;
	int					pole_to_resize;
}						t_coords;

typedef struct			s_lst
{
	int					id;
	char				letter;
	int					x[4];
	int					y[4];
	int					tmp_x[4];
	int					tmp_y[4];
	int					str_coord[4];
	struct s_lst		*prev;
	struct s_lst		*next;
}						t_lst;

void					ft_error(void);
int						check_symb(char *str);
int						check_slash_n1(char *str);
int						check_slash_n(char *str);
int						check_shape(char *str);
int						check(char *str);
char					*delete_sqr(char **square);
t_lst					*save_tetrimino(t_lst *head, char *buf, int len);
t_lst					*delete_listfrom_tail(t_lst **node);
int						calc_pohibku(t_lst *current);
void					convert_coord_to_descart(t_lst **node);
char					*make_smallest_square(int len);
int						calc_smallest_square(t_lst *head, int pole_to_resize);
void					rewrite_square(char **square, char c);
int						save_tetr_to_sqr(char **square, t_lst **node,
		t_coords *zdvig);
void					set_zdvig_to_zero(t_coords *zdvig);
void					place_my_tetrimino(t_lst **head, char **square);
void					rewrite_tmp_x_y(t_lst **current, int x, int y);
int						try_to_write_tetr(char *square, t_lst *node);
int						calc_pole(char *square);

#endif
