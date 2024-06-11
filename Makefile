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
LIBFT_DIR = ./Libft
SRCS_DIR = ./srcs
OBJ_DIR = ./srcs/temp
MLX_DIR = ./MLX42

#------------- SOURCE FILES ------#
CFILES = $(SRCS_DIR)/cub3d.c $(SRCS_DIR)/parsing.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/mlx.c \
      $(SRCS_DIR)/colors.c $(SRCS_DIR)/collision.c $(SRCS_DIR)/ray_casting.c

OFILES = $(CFILES:.c=.o)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

LIBS	= $(MLX_DIR)/build/libmlx42.a

ifeq ($(shell uname), Darwin)
	MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw #-framework Cocoa -framework OpenGL -framework IOKit
else
	MLX_LIBS = -L$(MLX_DIR)/build -lmlx42 -L"/User/$(USER)/.brew/opt/glfw/lib" -lglfw -ldl -pthread -lm 
endif

#--------- FLAGS ----------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast
HEADERS	= -I ./includes -I $(MLX_DIR)/include/MLX42/
DEBUGFLAGS = -g -fsanitize=address,undefined

#------------------#

all: libmlx $(NAME)

libmlx:
	@if [ ! -d $(MLX_DIR)/build ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4; \
	fi

debug: libmlx .debug

$(NAME): $(OFILES)
	@echo "$(COLOUR_BLUE)compiling $(NAME)$(COLOUR_END)"
	@make -C Libft
	@$(CC) $(CFLAGS) $(OFILES)  $(HEADERS) $(LIBS) $(MLX_LIBS) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME) 
	@echo "$(COLOUR_GREEN)$(NAME) compiled successfully$(COLOUR_END)"

.debug: $(OFILES) 	
	@echo "$(COLOUR_BLUE)compiling $(NAME) in debug mode$(COLOUR_END)"
	@make -C Libft
	@cc $(DEBUGFLAGS) $(OFILES) $(HEADERS) $(LIBS) $(MLX_LIBS) $(LIBFT_DIR)/$(LIBFTNAME) -o $(NAME) 
	@touch .debug
	@echo "$(COLOUR_GREEN)$(NAME) compiled successfully$(COLOUR_END)"

clean:
	@echo "$(COLOUR_GREEN)cleaning $(NAME)$(COLOUR_END)"
	@rm -f $(OFILES) 
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME) 
	make fclean -C $(LIBFT_DIR) 
	$(RM) $(NAME)
	$(RM) .debug
	$(RM) -r $(NAME).dSYM

re: fclean all 

.PHONY: all clean fclean re libmlx debug