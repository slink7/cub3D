/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:12:12 by scambier          #+#    #+#             */
/*   Updated: 2025/11/24 16:18:34 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"

t_err	load_map(t_map *out, char *path);
void	print_error(t_err code);

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
	return (0);
}
