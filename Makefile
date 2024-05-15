# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:27:18 by tclaereb          #+#    #+#              #
#    Updated: 2024/05/15 18:38:02 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_P = so_long

_SRCS = main.c \
		utils/ft_malloc.c \
		utils/garbage_collector.c \
		utils/short_utils.c \
		utils/short_utils2.c \
		utils/t_map/map_parsing.c \
		utils/t_map/map_new.c \
		utils/t_map/map_add_below.c \
		utils/t_map/map_add_right.c \
		utils/t_map/map_len.c \
		utils/t_map/map_link_lines.c \
		utils/t_map/map_validity.c \
		utils/t_map/find_symbol.c \
		utils/t_map/map_display.c \
		mlx/mlx_init.c \
		mlx/mlx_init_hooks.c \
		mlx/hooks/mlx_inputs.c \
		mlx/player/mlx_player.c \
		mlx/player/utils.c \
		mlx/player/moover.c \
		mlx/player/shooter.c \
		mlx/player/animate.c \
		mlx/player/animater.c \
		mlx/npc/npc.c \
		mlx/npc/moover.c \
		mlx/npc/kill_entity.c \
		mlx/npc/shooter.c \

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))

SRCO = $(SRCS:.c=.o)

MAKE_LIBFT = $(MAKE) -C ./libft
LIBFT = ./libft/libft.a

FLAG = -g3 -Wall -Wextra -Werror -fsanitize=address
INC = -I includes/

all : $(NAME_C) $(NAME_P)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME_P) : $(SRCO) | $(LIBFT)
	gcc $(FLAG) -o $(NAME_P) $(SRCO) $(LIBFT) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

%.o : %.c
	gcc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)
	$(MAKE_LIBFT) clean

fclean : clean
	/bin/rm -f $(NAME_P)
	$(MAKE_LIBFT) fclean

re :
	$(MAKE_LIBFT) fclean
	make fclean
	make
