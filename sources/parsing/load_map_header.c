/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:22:55 by scambier          #+#    #+#             */
/*   Updated: 2025/11/24 15:27:24 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"

t_err	extract_var(t_bst **bst, char *line)
{
	char	*temp;

	temp = ft_strchrf(line, ft_iswhitespace, 0);
	if (!temp)
		return (0 & ft_printf("Warning: missing value '%s' 0\n", line));
	temp[0] = 0;
	temp = ft_strchrf(temp + 1, ft_iswhitespace, 1);
	if (!temp)
		return (0 & ft_printf("Warning: missing value '%s' 1\n", line));
	ft_bst_setval(bst, line, temp);
	return (0);
}

char	*next_line(char **lines, int *line_index)
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

t_err	read_map_header(t_bst **infos, char **lines, int *line_index)
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

t_err	load_display(t_display *out, char *in)
{
	char	**rgb;

	if (ft_strncmp(in, "0x", 2) == 0)
	{
		out->type = COLOR;
		out->data.color.hexa = ft_atoi_base(in, "0123456789abcdef");
	}
	else if (ft_isdigit(in[0]))
	{
		out->type = COLOR;
		rgb = ft_split(in, ',');
		if (!rgb)
			return (ERR_MALLOC);
		if (ft_strarrlen(rgb) != 3)
			return (ft_strarrfree(rgb), 0 & ft_printf("Invalid color '%s'", in));
		out->data.color.rgba[R] = ft_atoi(rgb[0]) % 256;
		out->data.color.rgba[G] = ft_atoi(rgb[1]) % 256;
		out->data.color.rgba[B] = ft_atoi(rgb[2]) % 256;
		ft_strarrfree(rgb);
	}
	else
	{
		out->type = PATH;
		out->data.path = in;
	}
	return (0);
}

t_err	parse_map_header(t_map *map, t_bst *infos)
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
	k = -1;
	while (++k < (sizeof(required_var) / sizeof(char *)))
	{
		value = ft_bst_getval(infos, required_var[k]);
		if (!value)
			return (ERR_HEADER & ft_printf("Warning: Missing '%s'", required_var[k]));
		load_display(&map->displays[k], value);
	}
	return (0);
}

t_err	handle_map_header(t_map *map, char **lines, int *line_index)
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
	return (ft_bst_free(&infos), 0);
}
