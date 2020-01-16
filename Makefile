# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nphilipp <nphilipp@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/06 14:01:22 by nphilipp       #+#    #+#                 #
#    Updated: 2020/01/16 17:21:51 by nphilipp      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = new_raycaster.c cud3d_read_map.c cud3d_utils.c main_cud3d.c \
map_check.c cub3d_color.c 

FLAGS = -O3

INC = /minilibx_mms_20191025_beta/ -Lminilibx_mms_20191025_beta -lmlx

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -I $(INC) -o cud3d

clean: fclean

fclean:
	rm -f cud3d

re: fclean all