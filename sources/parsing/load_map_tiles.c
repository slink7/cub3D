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

#include "cub3D.h"
#include "mem.h"
#include "str.h"



t_err	load_map_tiles(t_map *map, char **lines, int *line_index)
{
	int	len;
	int	k;

	len = ft_strarrlen(lines + *line_index);
	map->tiles = ft_calloc(sizeof(char *), len + 1);
	if (!map->tiles)
		return (ERR_MALLOC);
	k = -1;
	while (++k < len)
	{
		map->tiles[k] = ft_strdup(lines[*line_index + k]);
		if (!map->tiles[k])
			return (ERR_MALLOC);
	}
	return (0);
}
