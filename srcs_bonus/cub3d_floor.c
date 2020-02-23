/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_floor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 19:42:14 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/22 16:39:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_fc_pixels(t_map_data *mdata, t_data *data, \
				t_vsi *dem, t_vsi tex_dem)
{
	char			*str;
	unsigned int	color;

	if (!(*data).textures.floor)
	{
		str = (*data).textures.floor_tex.img_addr + ((*data).textures.floor_tex\
		.size_line * tex_dem.y + tex_dem.x * \
		(*data).textures.floor_tex.bits_per_pixel / 8);
		color = *(unsigned int *)str;
		put_pixel(data, (*dem).x, (*dem).y, color);
	}
	if (!(*data).textures.clg)
	{
		str = (*data).textures.clg_tex.img_addr + ((*data).textures.\
		clg_tex.size_line * tex_dem.y + tex_dem.x * \
		(*data).textures.clg_tex.bits_per_pixel / 8);
		color = *(unsigned int *)str;
		put_pixel(data, (*dem).x, (*mdata).dem_y - (*dem).y - 1, color);
	}
}

void	calculate_tex_start(t_vsi *tex_dem, \
		t_vsi cell, t_texture tex, t_floor *f_data)
{
	(*tex_dem).x = (int)(tex.width * ((*f_data).floor_x - cell.x));
	(*tex_dem).y = (int)(tex.height * ((*f_data).floor_y - cell.y));
}

void	cast_floor(t_map_data *mdata, t_floor *f_data, t_vsi *dem, t_data *data)
{
	t_vsi	cell;
	t_vsi	tex_dem;

	(*dem).x = 0;
	while ((*dem).x < (*mdata).dem_x)
	{
		cell.x = (int)(*f_data).floor_x;
		cell.y = (int)(*f_data).floor_y;
		if (!(*data).textures.floor)
		{
			calculate_tex_start(&tex_dem, cell, \
					(*data).textures.floor_tex, f_data);
		}
		else
		{
			calculate_tex_start(&tex_dem, cell, \
					(*data).textures.clg_tex, f_data);
		}
		(*f_data).floor_x += (*f_data).step_x;
		(*f_data).floor_y += (*f_data).step_y;
		put_fc_pixels(mdata, data, dem, tex_dem);
		(*dem).x++;
	}
}

void	make_floor(t_map_data *mdata, t_data *data)
{
	t_vsi	dem;
	double	rowdistance;
	int		p;
	double	pos_z;
	t_floor	f_data;

	dem.y = (*mdata).dem_y / 2 + 1;
	while (dem.y < (*mdata).dem_y)
	{
		f_data.dir1.y = (*mdata).dir_y - (*mdata).plane_y;
		f_data.dir2.y = (*mdata).dir_y + (*mdata).plane_y;
		f_data.dir1.x = (*mdata).dir_x - (*mdata).plane_x;
		f_data.dir2.x = (*mdata).dir_x + (*mdata).plane_x;
		p = dem.y - (*mdata).dem_y / 2;
		pos_z = 0.5 * (*mdata).dem_y;
		rowdistance = pos_z / p;
		f_data.step_x = rowdistance * (f_data.dir2.x \
						- f_data.dir1.x) / (*mdata).dem_x;
		f_data.step_y = rowdistance * (f_data.dir2.y - \
							f_data.dir1.y) / (*mdata).dem_x;
		f_data.floor_x = (*mdata).pos_x + rowdistance * f_data.dir1.x;
		f_data.floor_y = (*mdata).pos_y + rowdistance * f_data.dir1.y;
		cast_floor(mdata, &f_data, &dem, data);
		dem.y++;
	}
}
