# **************************************************************************** #
#                                                                               #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 11:59:53 by clundber          #+#    #+#              #
#    Updated: 2024/02/16 12:18:31 by clundber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# ------------ PROJECT -------#
NAME = cub3d
LIBFTNAME = libft.a

# ------------ DIRECTORIES ---#
LIBFT_DIR = ./libft
SRCS_DIR = ./srcs
OBJ_DIR = ./srcs/temp
MLX_DIR = ./MLX42

#------------- SOURCE FILES ------#
CFILES = $(SRCS_DIR)/cub3d.c $(SRCS_DIR)/parsing.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/mlx.c \
      $(SRCS_DIR)/colors.c

OFILES = $(CFILES:.c=.o)

LIBS	= $(MLX_DIR)/build/libmlx42.a

ifeq ($(shell uname), Darwin)
	MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw #-framework Cocoa -framework OpenGL -framework IOKit
else
	MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -L"/User/$(USER)/.brew/opt/glfw/lib" -lglfw -ldl -pthread -lm 
endif

#--------- FLAGS ----------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -Ofast
HEADERS	:= -I ./includes -I $(MLX_DIR)/include/MLX42/

all: libmlx $(NAME)

libmlx:
	@if [ ! -d $(MLX_DIR)/build ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4; \
	fi

$(NAME): $(OFILES)
	@echo "$(COLOUR_BLUE)compiling $(NAME)$(COLOUR_END)"
	@make -C libft
	@$(CC) $(CFLAGS) $(OFILES)  $(HEADERS) $(LIBS) $(MLX_LIBS) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME) 
	@echo "$(COLOUR_GREEN)$(NAME) compiled successfully$(COLOUR_END)"

clean:
	@echo "$(COLOUR_GREEN)cleaning $(NAME)$(COLOUR_END)"
	@rm -f $(OFILES) 
	@make clean -C libft/
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME) 
	@rm -f libft/libft.a

re: fclean all 

.PHONY: all clean fclean re libmlx