#include "libft.h"
#include "cub3D.h"

void	print_image(t_image *image, char *name)
{

	if (image && image->mlx_img)
		ft_printf("loaded %s image (%u, %u)\n", name, image->width,
			image->height);
	else
		ft_printf("unloaded %s image\n", name);
}

void	print_surface(t_surface *surface)
{
	t_texture		*texture;
	unsigned int	k;

	if (surface->type == COLOR)
		ft_printf("Color: %#08x\n", surface->data.color.raw);
	else
	{
		texture = surface->data.texture;
		ft_printf("Texture path: %s\n", texture->path);
		print_image(&texture->source, "source");
		if (!texture->image_count)
			return ;
		ft_printf("%u sub images\n", texture->image_count);
		k = -1u;
		while (++k < texture->image_count)
		{
			print_image(&texture->images[k][ALBEDO], "albedo");
			print_image(&texture->images[k][NORMAL], "normal");
		}
	}
}

void	print_map(t_map *map)
{
	int k;

	ft_printf("Map surfaces:\n");
	k = -1;
	while (++k < SURF_COUNT)
		print_surface(map->surfaces + k);
	ft_printf("Map tiles:\n");
	k = -1;
	while (map->tiles[++k])
		ft_printf("%s.\n", map->tiles[k]);

}
