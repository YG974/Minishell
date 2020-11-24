NAME	= cub3D
SRC 	= cub.c \
			parse.c \
			parse_map.c \
			wall_1.c \
			wall_2.c \
			sprite_1.c \
			sprite_2.c \
			move.c \
			key.c \
			utils.c \
			bitmap.c \
			utils_2.c \

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))
CC		= gcc
CFLAGS	= -O3 -Wall -Wextra -Werror -g
FT		= ./libft/
FT_MLX 	= ./minilibx-linux/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/libft
FT_LNK	= -L ./libft -l ft -l pthread
MLX_LNK	= -I ./minilibx-linux -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd
SRCDIR	= ./
INCDIR	= ./includes/
OBJDIR	= ./obj/
all: obj $(FT_LIB) $(FT_MLX) $(NAME)
obj:
	mkdir -p $(OBJDIR)
$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<
$(FT_LIB):
	make -C $(FT_MLX)
	make -C $(FT)
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) $(MLX_LNK) -lm -o $(NAME)
clean:
	rm -f *.o
	make -C $(FT) clean
	make -C $(FT_MLX) clean
fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean
	make -C $(FT_MLX) clean
re: fclean all

test: all
	./cub3D map.cub

save: all
	./cub3D map.cub --save
