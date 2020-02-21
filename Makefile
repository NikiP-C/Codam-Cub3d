# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/02/21 16:18:26 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = cub3d_raycaster.c cud3d_read_map.c cud3d_utils.c main_cud3d.c \
map_check.c cub3d_color.c cub3d_movement.c cud3d_keypress.c \
cub3d_sprites.c cub3d_2darray.c ft_calloc.c cub3d_project_sprites.c \
ft_put2dstr.c cub3d_bitmap.c cub3d_smooth_movement.c cub3d_floor.c \
cub3d_error.c cub3d_read_file.c cub3d_get_textures.c cub3d_dem.c \
cub3d_life.c cub3d_find_sprites.c

FLAGS = -O3 -Wall -Werror -Wextra

INC = /minilibx/ -Lminilibx -lmlx

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -I $(INC) -o cud3d

bonus: all

clean: fclean

fclean:
	rm -f cud3d

norm:
	norminette $(SRC)

re: fclean all
