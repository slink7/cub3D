/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:12:12 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 23:44:48 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"

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
	err = validate_map(&map);
	if (err)
		print_error(err);
	print_map(&map);
	return (0);
}
