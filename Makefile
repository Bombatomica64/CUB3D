# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:49:30 by lmicheli          #+#    #+#              #
#    Updated: 2024/05/16 17:52:17 by lmicheli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc -Wall -Wextra -Werror -g

MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

INCLUDES =	Includes/

PARSING =	parsing/map_check.c \
			parsing/var_init.c \
			parsing/splut.c \
			parsing/color.c

SRCS =	srcs/main.c \
		srcs/put_images.c \
		srcs/error_management.c
		
SRC = $(PARSING) $(SRCS)

FT_PRINTF = libft
LIB = libft/libftprintf.a

all: $(NAME)

$(NAME):
	@make all -C $(FT_PRINTF)
	@make all -C $(MLX_DIR)
	@$(CC) $(SRC) $(LIB) $(MLX) $(MLXFLAGS) -I $(INCLUDES) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

clean:
	@make clean -C $(FT_PRINTF)
	@make clean -C $(MLX_DIR)
	@rm -f $(OBJ)
	@echo "Cleaned "$(NAME)" and libft objects successfully!"
	
fclean: clean
	@make fclean -C $(FT_PRINTF)
	@make clean -C $(MLX_DIR)
	@rm -f $(NAME)
	@echo "Fcleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all

play:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) $(MLX) $(MLXFLAGS) -I $(INCLUDES) -o $(NAME)
	@echo "\033[34mRe-compiled "$(NAME)" successfully!\033[0m"
	@echo "\033[30mPlease work🙏\033[0m"
	@./$(NAME) maps/test.cub

val:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) $(MLX) $(MLXFLAGS) -I $(INCLUDES) -o $(NAME)
	@echo "\033[34mAre you ready for debugging?\033[0m 😈"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes ./$(NAME) maps/test.cub


.PHONY: all clean fclean re play val