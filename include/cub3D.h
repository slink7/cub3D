/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:10:01 by scambier          #+#    #+#             */
/*   Updated: 2025/11/18 22:51:27 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "bst.h"

#define R 0
#define G 1
#define B 2
#define A 3

typedef union u_color
{
	int		hexa;
	char	rgba[4];
}	t_color;

typedef union u_display_data
{
	t_color	color;
	char	*path;
}	t_display_data;

typedef enum e_display_type
{
	COLOR,
	PATH
}	t_display_type;

typedef struct s_display
{
	t_display_data	data;
	t_display_type	type;
}	t_display;

#define NO 0
#define EA 1
#define SO 2
#define WE 3

typedef struct s_map
{
	t_bst		*infos;
	char		**tiles;
}	t_map;

#endif
