# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/02/04 11:16:35 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = cub3d_raycaster.c cud3d_read_map.c cud3d_utils.c main_cud3d.c \
map_check.c cub3d_color.c srcs/cub3d_movement.c srcs/cud3d_keypress.c \
cub3d_sprites.c cub3d_2darray.c ft_calloc.c cub3d_project_sprites.c \
ft_put2dstr.c cub3d_bitmap.c

FLAGS = -O3 -Wall -Werror -Wextra

INC = /minilibx_mms_20191025_beta/ -Lminilibx_mms_20191025_beta -lmlx

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -I $(INC) -o cud3d

clean: fclean

fclean:
	rm -f cud3d

norm:
	norminette $(SRC)

re: fclean all