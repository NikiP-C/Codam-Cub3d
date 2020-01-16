/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cud3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 14:34:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/15 14:30:21 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minilibx_mms_20191025_beta/mlx.h>
#include <unistd.h>
#include "cud3d.h"
#include <stdint.h>

int	main(void)
{
	void *mlx;
	void *mlx_win;
	uint32_t color;
	int imgx;
	int height;
	int width;
	int imgy;
	void *mlx_img;
	t_data *data;
	int x;
	int y;

	x = 0;
	y = 0;
	color = 0x009dfcfb;
	mlx = mlx_init();
	if (mlx == 0)
		return (0);
	mlx_win = mlx_new_window(mlx, 600, 400, "Hello World!");
	mlx_img = mlx_png_file_to_image(mlx, "redbrick.png", &width, &height);
	//mlx_put_image_to_window(mlx, mlx_win, mlx_img, 10, 10);
	mlx_img = mlx_xpm_file_to_image(mlx, "purplestone.xpm", &width, &height);
	printf("height = %i, width = %i\n", height, width);
	while (y < height)
	{
		while (x < width)
		{
			color = *(uint32_t *)mlx_img + (imgy * width) + imgx;
			printf("color = %#x | ", color);
			imgx++;
			if (imgx == width)
			{
				imgy++;
				if (imgy == height)
					imgy = 0;
				imgx = 0;
			}
			if (y > 180 && y < 210 && x > 290 && x < 310)
				mlx_pixel_put(mlx, mlx_win, x, y, 0x00AA0000);
			else if (y > 170 && y < 270 && x > 70 && x < 120)
				mlx_pixel_put(mlx, mlx_win, x, y, 0x00AA0000);
			else
				mlx_pixel_put(mlx, mlx_win, x, y, color);
			x++;
		}
		x = 0;
		y++;
		if (y == 150)
			color = 0x00ffbd08;
		if (y == 200)
			color = 0x0003ad31;
	}
	mlx_loop(mlx);
	sleep(5);
	mlx_destroy_window(mlx, mlx_win);
}
