# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/02/22 19:56:36 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS = cub3D_bonus

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
		srcs/cub3d_floor.c \
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

$(NAME): libmx
	gcc $(FLAGS) $(SRC) -I $(INC) -o $(NAME)

bonus: $(BONUS)

$(BONUS): libmx
	gcc $(FLAGS) $(SRC) -I $(INC) -o $(BONUS)

libmx:
	make -C minilibx
	mv minilibx/libmlx.dylib .

clean: 
	make -C minilibx clean
	rm libmlx.dylib

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all
