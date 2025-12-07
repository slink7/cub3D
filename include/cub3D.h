/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:10:01 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 23:47:28 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "bst.h"
#include "color.h"
#include "ftmath.h"

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

#define NORTH		0
#define EAST		1
#define SOUTH		2
#define WEST		3
#define FLOOR		4
#define CEILING		5
#define SURF_COUNT	6

typedef struct s_player
{
	t_vec2f position;
	float	direction;
}	t_player;

typedef struct s_map
{
	t_surface	surfaces[SURF_COUNT];
	char		**tiles;
	int			width;
	int			height;
	t_player	player;
}	t_map;

// Error

#define ERR_WRONG	0
#define ERR_ARGS	1
#define ERR_MALLOC	2
#define ERR_HEADER	3
#define ERR_MAP		4
#define ERR_PLAYER	5

typedef unsigned int	t_err;

void	print_error(t_err code);

// Load map
t_err	load_map(t_map *out, char *path);
void	destroy_map(t_map *map);
// Load map header
t_err	load_map_header(t_map *out, char **lines, int *line_index);
// Load map tiles
t_err	validate_map(t_map *map);
t_err	load_map_tiles(t_map *map, char **lines, int *line_index);
// Texture list
t_texture	*create_texture(char *path);
void		delete_texture_list(void *mlx);
// debug
void	print_image(t_image *image, char *name);
void	print_surface(t_surface *surf);
void	print_map(t_map *map);
// error
void	print_error(t_err code);

#endif
