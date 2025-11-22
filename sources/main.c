/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:12:12 by scambier          #+#    #+#             */
/*   Updated: 2025/11/18 22:51:34 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"

#define ERR_WRONG	0
#define ERR_ARGS	1
#define ERR_MALLOC	2

const char	*error_list[] = {
	"Wrong error code",
	"Not enough arguments",
	"Malloc failed"
};

typedef unsigned int	t_err;

void	print_error(t_err code)
{
	if (code >= sizeof(error_list) / sizeof(char *))
		print_error(0);
	else
		ft_dprintf(2, "\e[38;2;255;0;0mError\n%s\n\e[0m", error_list[code]);
}

int	is_empty(int c)
{
	return (!!ft_strchr(" \t", c));
}

int	is_empty_str(char *str)
{
	return (!ft_strchrf(str, is_empty, 1));
}

int	isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

t_err	extract_var(t_bst **bst, char *line)
{
	char	*temp;

	temp = ft_strchrf(line, is_empty, 0);
	if (!temp)
		return (0 & ft_printf("Warning: missing value '%s' 0\n", line));
	temp[0] = 0;
	temp = ft_strchrf(temp + 1, is_empty, 1);
	if (!temp)
		return (0 & ft_printf("Warning: missing value '%s' 1\n", line));
	ft_bst_setvar(bst, line, temp);
	return (0);
}

char	*next_line(char **lines, int *line_index)
{
	char	*out;

	while (lines && lines[*line_index])
	{
		out = ft_strchrf(lines[(*line_index)++], is_empty, 1);
		if (out)
			return (out);
	}
	return (0);
}

t_err	load_map_header(t_map *map, char **lines, int *line_index)
{
	char	*line;
	t_err	err;

	line = next_line(lines, line_index);
	while (line && (is_empty_str(line) || isupper(line[0])))
	{
		err = extract_var(&map->infos, line);
		if (err)
			return (err);
		line = next_line(lines, line_index);
	}
	return (0);
}

int	load_map_tiles()
{
	return (0);
}

void	ft_bst_print(t_bst *bst)
{
	if (!bst)
		return ;
	ft_bst_print(bst->left);
	ft_printf("'%s'='%s'\n", bst->var->name, bst->var->value);
	ft_bst_print(bst->right);
}

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
	ft_bst_print(out->infos);
	ft_strarrfree(lines);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_err	err;

	if (argc == 1)
	{
		print_error(ERR_ARGS);
		return (1);
	}

	err = load_map(&map, argv[1]);
	if (err)
		print_error(err);

	ft_bst_free(&map.infos);

	return (0);
}
