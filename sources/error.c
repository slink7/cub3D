/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:03:51 by scambier          #+#    #+#             */
/*   Updated: 2025/11/24 15:15:03 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"

void	print_error(t_err code)
{
	const char	*error_list[] = {
		"Wrong error code",
		"Not enough arguments",
		"Malloc failed",
		"Incomplete map header"
	};

	if (code >= sizeof(error_list) / sizeof(char *))
		print_error(0);
	else
		ft_dprintf(2, "\e[38;2;255;0;0mError\n%s\n\e[0m", error_list[code]);
}


