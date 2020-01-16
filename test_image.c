/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_image.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 12:17:21 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/15 14:27:38 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minilibx_mms_20191025_beta/mlx.h>
#include <unistd.h>
#include "cud3d.h"

int	main(void)
{
	void *mlx;
	void *mlx_win;
	int *mlx_img;
	int width;
	int height;
	unsigned int color;
	int y = 0;
	int x = 0;
	int imgx = 0;
	int imgy = 0;
	char *path = "image/purplestone.xpm";

	mlx = mlx_init();
	if (mlx == 0)
		return (0);
	mlx_win = mlx_new_window(mlx, 600, 400, "Hello World!");
	mlx_img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	while (y < 400)
	{
		while (x < 600)
		{
			color = (int *)mlx_img[(imgy * width) + imgx];
			imgx++;
			if (imgx == width)
			{
				imgy++;
				if (imgy == height)
					imgy = 0;
				imgx = 0;
			}
			//printf("Color = %x, imgx = %i. imgy = %i\n", color, imgx, imgy);
			mlx_pixel_put(mlx, mlx_win, y, x, 0x0032a852);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_loop(mlx);
}
