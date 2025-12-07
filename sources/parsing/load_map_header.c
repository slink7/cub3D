/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:22:55 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 23:31:03 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "color.h"
#include "cub3D.h"

static t_err	extract_var(t_bst **bst, char *line)
{
	char	*temp;

	temp = ft_strchrf(line, ft_iswhitespace, 0);
	if (!temp)
		return (0 & ft_dprintf(2, "Warning: missing value '%s'\n", line));
	temp[0] = 0;
	temp = ft_strchrf(temp + 1, ft_iswhitespace, 1);
	if (!temp)
		return (0 & ft_dprintf(2, "Warning: missing value '%s'\n", line));
	if (!ft_bst_setval(bst, line, temp))
		return (ERR_MALLOC);
	return (0);
}

static char	*next_line(char **lines, int *line_index)
{
	char	*out;
	while (lines && lines[*line_index])
	{
		out = ft_strchrf(lines[(*line_index)++], ft_iswhitespace, 1);
		if (out)
			return (out);
	}
	return (0);
}

static t_err	read_map_header(t_bst **infos, char **lines, int *line_index)
{
	char	*line;
	t_err	error;

	(void) error;
	line = next_line(lines, line_index);
	while (line && (ft_str_iswhitespace(line) || ft_isupper(line[0])))
	{
		error = extract_var(infos, line);
		if (error)
			return (error);
		line = next_line(lines, line_index);
	}
	return (0);
}

static t_err	load_surface(t_surface *out, char *in)
{
	if (ft_atoc(&out->data.color, in))
		out->type = COLOR;
	else
	{
		out->type = TEXTURE;
		out->data.texture = create_texture(in);
		if (!out->data.texture)
			return (ERR_MALLOC);
	}
	return (0);
}

static t_err	parse_map_header(t_map *map, t_bst *infos)
{
	static char	*required_var[] = {
		"NO",
		"EA",
		"SO",
		"WE",
		"F",
		"C"
	};
	t_err			error;
	unsigned int	k;
	char			*value;

	(void) error;
	k = -1u;
	while (++k < (sizeof(required_var) / sizeof(char *)))
	{
		value = ft_bst_getval(infos, required_var[k]);
		if (!value)
			return (ERR_HEADER & ft_printf("Warning: Missing '%s'", required_var[k]));
		load_surface(&map->surfaces[k], value);
	}
	return (0);
}

t_err	load_map_header(t_map *map, char **lines, int *line_index)
{
	t_bst	*infos;
	t_err	err;

	infos = 0;
	err = read_map_header(&infos, lines, line_index);
	if (err)
		return (ft_bst_free(&infos), err);
	err = parse_map_header(map, infos);
	if (err)
		return (ft_bst_free(&infos), err);
	ft_bst_print(infos);
	return (ft_bst_free(&infos), 0);
}
