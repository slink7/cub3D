#include "libft.h"
#include "cub3D.h"

void	print_display(t_display *d)
{
	if (d->type == COLOR) {
		ft_printf("Type Color: %d (%d, %d, %d)\n", d->data.color.hexa, d->data.color.rgba[R], d->data.color.rgba[G], d->data.color.rgba[B]);
	} else if (d->type == PATH) {
		ft_printf("Type Path: %s\n", d->data.path);
	}
}
