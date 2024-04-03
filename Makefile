# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:27:18 by tclaereb          #+#    #+#              #
#    Updated: 2024/04/03 11:09:20 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_P = so_long

_SRCS = main.c \
		map_parsing.c \
		utils/errors.c \
		utils/ft_malloc.c \
		utils/garbage_collector.c \
		utils/short_utils.c \
		utils/t_map/map_new.c \
		utils/t_map/map_add_below.c \
		utils/t_map/map_add_right.c \
		utils/t_map/map_link_lines.c \
		utils/t_map/map_validity.c \
		utils/t_map/map_display.c \

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))

SRCO = $(SRCS:.c=.o)

MAKE_LIBFT = $(MAKE) -C ./libft
LIBFT = ./libft/libft.a

FLAG = -g -Wall -Wextra -Werror
INC = -I includes/

all : $(NAME_C) $(NAME_P)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME_P) : $(SRCO) | $(LIBFT)
	gcc -o $(NAME_P) $(SRCO) $(LIBFT) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

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
