/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:13:49 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/21 16:17:38 by nphilipp      ########   odam.nl         */
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
# include <minilibx/mlx.h>

typedef struct		s_vsi
{
	int				y;
	int				x;
}					t_vsi;

typedef struct		s_vs
{
	double			y;
	double			x;
	char			sprite;
}					t_vs;

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

typedef struct		s_floor
{
	double			floor_y;
	double			floor_x;
	double			step_y;
	double			step_x;
	int				y;
	t_vs			dir1;
	t_vs			dir2;
}					t_floor;

typedef struct		s_movement
{
	int				forward;
	int				backwards;
	int				right;
	int				left;
	int				look_right;
	int				look_left;
}					t_movement;

typedef struct		s_keys
{
	int				walk_forward;
	int				walk_backwards;
	int				walk_right;
	int				walk_left;
	int				look_right;
	int				look_left;
	int				exit;
}					t_keys;

typedef struct		s_map_data
{
	int				x;
	int				y;
	int				dem_x;
	int				dem_y;
	double			pos_x;
	double			pos_y;
	double			dir_y;
	double			dir_x;
	double			plane_y;
	double			plane_x;
	char			*map;
	t_vs			*spr;
	char			**map2d;
	int				amouth_of_sprites;
}					t_map_data;

typedef struct		s_texture
{
	int				height;
	int				width;
	void			*img;
	int				endian;
	int				bits_per_pixel;
	int				size_line;
	char			*img_addr;
}					t_texture;

typedef struct		s_dda
{
	int				map_x;
	int				map_y;
	double			sidedis_x;
	double			sidedis_y;
	double			deltadis_x;
	double			deltadis_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			perpwall_dist;
	int				step_x;
	int				step_y;
	double			*buffer;
	int				hit;
	int				side;
	double			jump;
	double			life;
}					t_dda;

typedef struct		s_textures_data
{
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_texture		sprite_1;
	t_texture		sprite_2;
	t_texture		floor_tex;
	t_texture		clg_tex;
	int				floor;
	int				clg;
}					t_textures_data;

typedef struct		s_wall_size
{
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				color;
}					t_wall_size;

typedef struct		s_mlx_img
{
	void			*mlx_addr;
	void			*mlx_img;
	int				bits_per_pixel;
	int				endian;
	int				line_lenght;
}					t_mlx_img;

typedef struct		s_mlx_data
{
	void			*mlx;
	void			*mlx_win;
	t_mlx_img		*current_img;
	t_mlx_img		img_1;
	t_mlx_img		img_2;
}					t_mlx_data;

typedef struct		s_error
{
	int				south;
	int				north;
	int				west;
	int				east;
	int				sprite1;
	int				sprite2;
	int				clg;
	int				floor;
}					t_error;

typedef struct		s_data
{
	t_map_data		map_data;
	t_textures_data	textures;
	t_mlx_data		mlx_data;
	t_dda			dda;
	t_wall_size		wall_size;
	t_movement		move;
	t_keys			keys;
	int				safe;
}					t_data;

int					check_map(t_map_data *data);
void				make_frame(t_data *data);
t_data				*read_file(t_data *data, char *str);
char				*ft_realloc(char *str, int malloc_size);
t_data				*pick_color(t_data *data, int x);
void				put_pixel(t_data *data, int x, int y, int color);
t_data				*pick_texture(t_data *data, int x, t_texture *tex);
t_data				*choose_side(t_data *data, int x);
t_data				*sprites(t_data *data);
int					print_error(int error_code, char c);
int					key_press(int keycode, void *param);
t_data				*move_forward(t_data *data);
t_data				*move_backwards(t_data *data);
t_data				*turn_left(t_data *data);
t_data				*turn_right(t_data *data);
void				make_map2d(t_map_data *data);
void				put_healthbar(t_data *data);
t_map_data			*sprite_data(t_map_data *data, int j, int i);
t_data				*sprites(t_data *data);
t_data				*move_left(t_data *data);
t_data				*move_right(t_data *data);
void				twod_array_printer(char **array);
int					check_top_bottom(t_map_data *data);
int					end_session(t_data *data);
char				*ft_strchr_no_null(const char *s, int c);
t_map_data			*get_pos(int i, int j, t_map_data *data, char c);
void				is_map_closed(t_map_data *data);
void				*ft_calloc(size_t count, size_t size);
void				project_sprites(t_data *data, int *order);
t_sprite_data		*sprite_start_end(t_data *data, t_sprite_data *s_data);
t_sprite_data		*get_info(t_sprite_data *s_data, t_data *data, t_vs sprite);
void				make_bitmap(t_data *data);
int					movement(void *param);
int					key_release(int keycode, void *param);
int					end_session(t_data *data);
void				ft_bzero(void *s, size_t n);
void				map_checking(t_map_data *data);
void				make_floor(t_map_data *mdata, t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
int					error_double(char c, int error_code);
int					error_missing(int error_code);
t_map_data			*get_map(int fd, t_map_data *map_data, char c);
void				get_dem(int fd, char c, t_data *data);
int					make_string_realloc(int fd, char b, \
							char *str, int malloc_size);
t_map_data			*get_map(int fd, t_map_data *map_data, char c);
void				get_textures(t_data *data, int fd, char c, t_error *error);
void				death_screen(t_data *data);
int					flood_fill(char **map, int x, int y);
void				free_2darray(char **str);
void				find_sprites(t_map_data *data);

#endif
