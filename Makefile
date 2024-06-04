# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marco <marco@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:49:30 by lmicheli          #+#    #+#              #
#    Updated: 2024/06/04 12:38:30 by lmicheli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS_NAME = cub3D_bonus

CC = cc -Wall -Wextra -Werror -g -lm

MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

INCLUDES =	Includes/

PARSING =	parsing/map_check.c \
			parsing/var_init.c \
			parsing/splut.c \
			parsing/color.c \
			parsing/textures.c \
			parsing/player.c \
			parsing/char_checks.c \
			parsing/floor_ceiling.c \
			parsing/get_textures.c

RAYCASTING =	raycasting/distance.c \
				raycasting/rays.c \
				raycasting/pixel_putting.c \
				raycasting/pixels.c \
				raycasting/render.c \
				raycasting/frame_to_render.c \
				raycasting/dda.c

SRCS =	srcs/main.c \
		srcs/put_images.c \
		srcs/error_management.c \
		srcs/fast_trig.c \
		srcs/vectors.c \
		srcs/mouse.c \
		srcs/keyboard.c

BONUS =	bonus/minimap.c \
		bonus/bonus_init.c \
		bonus/sprites.c \
		bonus/animations.c \
		bonus/doors.c

SRC = $(PARSING) $(SRCS) $(RAYCASTING)

SRC_BONUS = $(PARSING) $(SRCS) $(RAYCASTING) $(BONUS)

FT_PRINTF = libft
LIB = libft/libftprintf.a

all: $(NAME)

$(NAME):
	@make all -C $(FT_PRINTF)
	@make all -C $(MLX_DIR)
	@$(CC) $(SRC) $(LIB) $(MLX) $(MLXFLAGS) -DBONUS=0 -I $(INCLUDES) -o $(NAME)
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
	@rm -f $(BONUS_NAME)
	@echo "Fcleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all

rebonus: fclean bonus

bonus: $(BONUS_NAME)

$(BONUS_NAME):
	@make all -C $(FT_PRINTF)
	@make all -C $(MLX_DIR)
	@$(CC) $(SRC_BONUS) $(LIB) $(MLX) $(MLXFLAGS) -DBONUS=1 -I $(INCLUDES) -o $(BONUS_NAME)
	@echo "Compiled "$(BONUS_NAME)" successfully!" 

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