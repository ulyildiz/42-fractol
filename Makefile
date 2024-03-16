NAME = fractol
CC = cc -Wall -Wextra -Werror -g
SRC = calculate_set.c \
		check.c \
		draw.c \
		fractol.c \
		free_error.c \
		hook.c \
		utils.c 
OBJ = $(SRC:.c=.o)
MLX_LIB = mlx/libmlx.a  


$(NAME): $(OBJ)
	@make -C mlx/
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@
all: $(NAME)

.c.o:
	$(CC) -c -o $@ $<

clean:
	@make -C mlx/ clean
	@rm -rf *.o
fclean: clean
	@rm -rf $(MLX_LIB)
	@rm -rf $(NAME)
re: fclean all

.PHONY: re fclean clean all