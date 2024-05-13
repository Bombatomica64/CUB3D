# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 10:49:30 by lmicheli          #+#    #+#              #
#    Updated: 2024/05/13 18:11:41 by lmicheli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

cc = cc -Wall -Wextra -Werror -g 

MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

INCLUDES = Includes/functions.h \
			Includes/structs.h

PARSING =	parsing/map_check.c \
			parsing/var_init.c

SRCS = srcs/main.c \
		
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
	@make fclean -C $(MLX_DIR)
	@rm -f $(NAME)
	@echo "Fcleaned "$(NAME)" and fclean libft successfully!"
	
re: fclean all

play:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mRe-compiled "$(NAME)" successfully!\033[0m"
	@echo "\033[30mPlease work🙏\033[0m"
	@./$(NAME)

val: clean $(SRC)
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIB) -o $(NAME) -lreadline
	@echo "\033[34mAre you ready for debugging?\033[0m 😈"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s --track-fds=yes ./$(NAME)


.PHONY: all clean fclean re play val