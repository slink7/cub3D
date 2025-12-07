/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_tiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:30:13 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 23:48:06 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>

#include "cub3D.h"
#include "mem.h"
#include "str.h"
#include "ft_printf.h"

int	is_edge(t_map *map, int x, int y)
{
	return (x == 0 || y == 0 || x == map->width - 1|| y == map->height - 1);
}

bool	check_tile(t_map *map, int x, int y)
{
	//TODO: CHECK LES ' ' MEME SUR LES BORDS
	if (is_edge(map, x, y))
		return (!!ft_strchr(" #", map->tiles[y][x]));
	if (map->tiles[y][x] != ' ')
		return (true);
	if (!ft_strchr(" #", map->tiles[y][x - 1]) || !ft_strchr(" #", map->tiles[y - 1][x])
		|| !ft_strchr(" #", map->tiles[y][x + 1]) || !ft_strchr(" #", map->tiles[y + 1][x]))
		return (false);
	return (true);
}

t_err	is_map_enclosed(t_map *map)
{
	int		x;
	int		y;

	y = -1;
	while (map->tiles[++y])
	{
		x = -1;
		while (map->tiles[y][++x])
		{
			if (!check_tile(map, x, y))
			{
				ft_dprintf(2, "Warning: unclosed map at (%d, %d)\n", x, y);
				return (ERR_MAP);
			}
		}
	}
	return (0);
}

t_err	check_player(t_map *map)
{
	int		x;
	int		y;
	int		index;
	bool	has_player;

	has_player = false;
	y = -1;
	while (map->tiles[++y])
	{
		x = 0;
		while (map->tiles[y][x])
		{
			index = ft_strchri("ENWS", map->tiles[y][x]);
			if (index != -1)
			{
				if (has_player) {
					ft_dprintf(2, "Warning: Too many players !\n");
					return (ERR_PLAYER);
				}
				has_player = true;
				map->player.position = (t_vec2f){(float)x, (float)y};
				map->player.direction = (float)index * M_PI / 2.0f;
			}
			x++;
		}
	}
	if (!has_player)
		ft_dprintf(2, "Warning: Missing player !\n");
	return (!has_player * ERR_PLAYER);
}

t_err	validate_map(t_map *map)
{
	t_err	(*tests[])(t_map*) = {
		is_map_enclosed,
		check_player,
	};
	unsigned int	k;
	t_err			code;

	k = -1u;
	while (++k < sizeof(tests) / sizeof(t_err (*)(t_map*)))
	{
		code = tests[k](map);
		if (code)
			return (code);
	}
	return (0);
}

static int	max_length_calculator(char **lines)
{
	int	k;
	int	max_length;
	int	line_length;

	max_length = 0;
	k = -1;
	while (lines[++k])
	{
		line_length = ft_strlen(lines[k]);
		if (line_length > max_length)
			max_length = line_length;
	}
	return (max_length);
}

t_err	load_map_tiles(t_map *map, char **lines, int *line_index)
{
	int	height;
	int	line_len;
	int	k;

	height = ft_strarrlen(lines + *line_index);
	map->height = height;
	map->tiles = ft_calloc(sizeof(char *), height + 1);
	if (!map->tiles)
		return (ERR_MALLOC);
	map->width = max_length_calculator(&lines[*line_index]);
	k = -1;
	while (++k < height)
	{
		map->tiles[k] = ft_calloc(sizeof(char), map->width + 1);
		if (!map->tiles[k])
			return (ERR_MALLOC);
		line_len = ft_strlen(lines[*line_index]);
		ft_memcpy(map->tiles[k], lines[*line_index], line_len);
		ft_memset(&map->tiles[k][line_len], ' ', map->width - line_len);
		++*line_index;
		map->tiles[k][map->width] = 0;
	}
	return (0);
}
