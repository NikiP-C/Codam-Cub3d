# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/02/22 14:25:51 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

BONUS = cub3d_bonus

SRC =	srcs/cub3d_raycaster.c \
		srcs/cud3d_read_map.c \
		srcs/cud3d_utils.c \
		srcs/main_cud3d.c \
		srcs/map_check.c \
		srcs/cub3d_color.c \
		srcs/cub3d_movement.c \
		srcs/cud3d_keypress.c \
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

$(NAME):
	gcc $(FLAGS) $(SRC) -I $(INC) -o $(NAME)

bonus: $(BONUS)

$(BONUS):
	gcc $(FLAGS) $(SRC) -I $(INC) -o $(BONUS)


clean: fclean

fclean:
	rm -f $(NAME)
	rm -f $(BONUS)

norm:
	norminette $(SRC)

re: fclean all
