# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student_bonus.codam.      +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/02/27 13:36:53 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS = cub3D_bonus

SRC_BONUS =	srcs_bonus/cub3d_raycaster_bonus.c \
			srcs_bonus/cub3d_read_map_bonus.c \
			srcs_bonus/cub3d_utils_bonus.c \
			srcs_bonus/cub3d_main_bonus.c \
			srcs_bonus/map_check_bonus.c \
			srcs_bonus/cub3d_color_bonus.c \
			srcs_bonus/cub3d_movement_bonus.c \
			srcs_bonus/cub3d_keypress_bonus.c \
			srcs_bonus/cub3d_sprites_bonus.c \
			srcs_bonus/cub3d_2darray_bonus.c \
			srcs_bonus/ft_calloc.c \
			srcs_bonus/cub3d_project_sprites_bonus.c \
			srcs_bonus/cub3d_bitmap_bonus.c \
			srcs_bonus/cub3d_smooth_movement_bonus.c \
			srcs_bonus/cub3d_floor_bonus.c \
			srcs_bonus/cub3d_error_bonus.c \
			srcs_bonus/cub3d_read_file_bonus.c \
			srcs_bonus/cub3d_get_textures_bonus.c \
			srcs_bonus/cub3d_dem_bonus.c \
			srcs_bonus/cub3d_life_bonus.c \
			srcs_bonus/cub3d_find_sprites_bonus.c \
			srcs_bonus/cub3d_path_bonus.c

SRC =	srcs/cub3d_raycaster.c \
		srcs/cub3d_read_map.c \
		srcs/cub3d_utils.c \
		srcs/cub3d_main.c \
		srcs/map_check.c \
		srcs/cub3d_color.c \
		srcs/cub3d_movement.c \
		srcs/cub3d_keypress.c \
		srcs/cub3d_sprites.c \
		srcs/cub3d_2darray.c \
		srcs/ft_calloc.c \
		srcs/cub3d_project_sprites.c \
		srcs/cub3d_bitmap.c \
		srcs/cub3d_smooth_movement.c \
		srcs/cub3d_error.c \
		srcs/cub3d_read_file.c \
		srcs/cub3d_get_textures.c \
		srcs/cub3d_dem.c \
		srcs/cub3d_life.c \
		srcs/cub3d_find_sprites.c \
		srcs/cub3d_path.c

FLAGS = -O3 -Wall -Werror -Wextra

INC = /minilibx/ -Lminilibx -lmlx

all: $(NAME)

$(NAME):
	make -C minilibx
	mv minilibx/libmlx.dylib .
	gcc $(FLAGS) $(SRC) -I $(INC) -o $(NAME)

bonus: $(BONUS)

$(BONUS):
	make -C minilibx
	mv minilibx/libmlx.dylib .
	gcc $(FLAGS) $(SRC_BONUS) -I $(INC) -o $(BONUS)

clean:
	make -C minilibx clean
	rm -f libmlx.dylib

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all
