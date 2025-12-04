/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:01:07 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 23:56:05 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"



t_err	load_map_tiles(t_map *map, char **lines, int *line_index);

t_err	load_map(t_map *out, char *path)
{
	char	*temp;
	char	**lines;
	int		line_index;
	t_err	err;

	ft_memset(out, 0, sizeof(t_map));
	ft_get_file(&temp, path, 256);
	lines = ft_split(temp, '\n');
	free(temp);
	line_index = 0;
	err = load_map_header(out, lines, &line_index);
	if (err)
		return (err);
	line_index--;
	err = load_map_tiles(out, lines, &line_index);
	if (err)
		return (err);
	ft_strarrfree(lines);
	return (0);
}
