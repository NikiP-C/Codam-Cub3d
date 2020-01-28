/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:13:49 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/28 12:02:22 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUD3D_H
# define CUD3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdint.h>
# include <minilibx_mms_20191025_beta/mlx.h>

typedef struct		s_sprite_data
{
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			trans_x;
	double			trans_y;
	int				spritescreen_x;
	int				sprite_height;
	int				sprite_width;
	int				drawstart_y;
	int				drawend_y;
	int				drawstart_x;
	int				drawend_x;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
}					t_sprite_data;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			distance;
	struct s_sprite *next;
}					t_sprite;

typedef struct 		s_vs
{
	double 			y;
	double			x;
}					t_vs;

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
	double		**spr;
	t_sprite	*sprite;
	t_vs		*head;
	char		**map2d;
	int			amouth_of_sprites;
}				t_map_data;

typedef struct	s_texture
{
	int			height;
	int			width;
	void		*img;
	int			endian;
	int			bits_per_pixel;
	int			size_line;
	char		*img_addr;
}				t_texture;

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
	double		*buffer;
	int			hit;
	int			side;
	double		jump;
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
}					t_data;

int			check_map(t_map_data *data);
void		make_frame(t_data *data);
t_data		*read_map(t_data *data, char *str);
char		*ft_realloc(char *str, int malloc_size);
t_data		*pick_color(t_data *data, int x);
void		put_pixel(t_data *data, int x, int y, int color);
t_data		*pick_texture(t_data *data, int x, t_texture *tex);
t_data 		*choose_side(t_data *data, int x);
t_data 		*sprites(t_data *data);
int			print_error(int error_code, char c);
int			key_press(int keycode, void *param);
int			move_forward(t_data *data);
int			move_backwards(t_data *data);
int			turn_left(t_data *data);
int			turn_right(t_data *data);
t_map_data	*make_map2d(t_map_data *data);
void		put_healthbar(t_data *data);
t_map_data	*sprite_data(t_map_data *data, int j, int i);
t_data		*sprites(t_data *data);
int			move_left(t_data *data);
int			move_right(t_data *data);
void		twod_array_printer(char **array);
int			check_top_bottom(t_map_data *data);
int			end_session(t_data *data);
char		*ft_strchr_no_null(const char *s, int c);
t_map_data	*get_pos(int i, int j, t_map_data *data, char c);
void		is_map_closed(t_map_data *data);
void		*ft_calloc(size_t count, size_t size);
void		ft_lstadd_back(t_sprite **alst, t_sprite *new);

#endif