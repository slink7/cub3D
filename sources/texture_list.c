/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:08:57 by scambier          #+#    #+#             */
/*   Updated: 2025/12/01 02:49:53 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cub3D.h"
#include "mlx.h"

static t_list	**get_texture_list()
{
	static t_list	*texture_list = 0;

	return (&texture_list);
}

t_texture	*create_texture(char *path)
{
	t_list		**list;
	t_list		*temp_list;
	t_texture	*out;

	out = ft_calloc(sizeof(t_texture), 1);
	if (!out)
		return (NULL);
	out->path = ft_strdup(path);
	if (!out->path)
		return (free(out), NULL);
	temp_list = ft_lstnew(out);
	if (!temp_list)
		return (free(out->path), free(out), NULL);
	list = get_texture_list();
	ft_lstadd_back(list, temp_list);
	return (out);
}

static void	delete_texture(void *content, void *mlx)
{
	t_texture		*texture;
	unsigned int	k;

	texture = (t_texture *)content;
	ft_free((void **)&texture->path, 0);
	mlx_destroy_image(mlx, texture->source.mlx_img);
	k = -1u;
	while (++k < texture->image_count)
	{
		mlx_destroy_image(mlx, texture->images[k][ALBEDO].mlx_img);
		if (texture->images[k][NORMAL].mlx_img)
			mlx_destroy_image(mlx, texture->images[k][NORMAL].mlx_img);
	}
	ft_free((void **)texture, 0);
}

void	delete_texture_list(void *mlx)
{
	t_list	**list;

	list = get_texture_list();
	ft_lstclear_arg(list, delete_texture, mlx);
}
