/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:10:01 by scambier          #+#    #+#             */
/*   Updated: 2025/11/30 19:14:37 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "bst.h"

#define R 0
#define G 1
#define B 2
#define A 3

typedef struct s_image
{
	void			*mlx_img;
	char			*data;
	unsigned int	width;
	unsigned int	height;
	unsigned int	endian;
	unsigned int	bpp;
}	t_image;

#define ALBEDO 0
#define NORMAL 1

typedef struct s_texture
{
	char			*path;
	t_image			source;
	t_image			*images[2];
	unsigned int	image_count;
}	t_texture;


typedef union u_color
{
	int		hexa;
	char	rgba[4];
}	t_color;


typedef union u_surface_data
{
	t_color		color;
	t_texture	*texture;
}	t_surface_data;


typedef enum e_surface_type
{
	COLOR,
	TEXTURE,
}	t_surface_type;

typedef struct s_surface
{
	t_surface_data	data;
	t_surface_type	type;
}	t_surface;

#define NORTH	0
#define EAST	1
#define SOUTH	2
#define WEST	3
#define FLOOR	4
#define CEILING	5

typedef struct s_map
{
	t_surface	surfaces[6];
	char		**tiles;
}	t_map;

// Error

#define ERR_WRONG	0
#define ERR_ARGS	1
#define ERR_MALLOC	2
#define ERR_HEADER	3

typedef unsigned int	t_err;

void	print_error(t_err code);

// Load map header

t_err	handle_map_header(t_map *out, char **lines, int *line_index);

#endif
