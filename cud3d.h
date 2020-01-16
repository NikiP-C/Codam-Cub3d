/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:13:49 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/16 19:16:04 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUD3D_H
# define CUD3D_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <minilibx_mms_20191025_beta/mlx.h>

typedef struct	s_map_data
{
	int			x;
	int			y;
	int			dem_x;
	int			dem_y;
	double		pos_x;
	double		pos_y;
	double		dir_y;
	double		dir_x;
	double		plane_y;
	double		plane_x;
	char		*map;
	char		**map2d;
}				t_map_data;

typedef struct s_texture
{
	int			height;
	int			width;
	void		*img;
	int			endian;
	int			bits_per_pixel;
	int			size_line;
	char		*img_addr;
}				t_texture;

typedef struct s_sprite
{
	double		*buffer;
	void		*img;
	int			endian;
	int			bits_per_pixel;
	int			size_line;
	char		*img_addr;
}				t_sprite;

typedef struct	s_dda
{
	int			map_x;
	int			map_y;
	double		sidedis_x;
	double		sidedis_y;
	double		deltadis_x;
	double		deltadis_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		perpwall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_dda;

typedef struct	s_textures_data 
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	t_texture	*sprite;
	int			floor;
	int			ceiling;
}				t_textures_data;

typedef struct	s_wall_size
{
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
}				t_wall_size;

typedef struct	s_mlx_data
{
	void		*mlx;
	void		*mlx_win;
	void		*mlx_addr;
	void		*mlx_img;
	int			bits_per_pixel;
	int			endian;
	int			line_lenght;
}				t_mlx_data;

typedef struct		s_data
{
	t_map_data		*map_data;
	t_textures_data	*textures;
	t_mlx_data		*mlx_data;
	t_dda			*dda;
	t_wall_size		*wall_size;
	t_sprite		*sprite;
}					t_data;

int		check_map(t_map_data *data);
void	make_frame(t_data *data);
t_data	*read_map(t_data *data);
char	*ft_realloc(char *str, int malloc_size);
t_data	*pick_color(t_data *data, int x);
void	put_pixel(t_data *data, int x, int y, int color);
t_data	*pick_texture(t_data *data, int x, t_texture *tex);
t_data *choose_side(t_data *data, int x);
t_data *sprites(t_data *data);

#endif