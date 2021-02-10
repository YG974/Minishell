NAME			= minishell

# FLAGS
CC				= clang
C_FLAGS			= -Wall -Wextra -Werror -g

# DIRECTORIES
SRCS_DIR		= ./srcs/
BUILDING_DIR	= ./building_dir/
INCLUDES_DIR	= ./includes/
LIB_DIR			= ./libft/

# LIBRARIES
LIB_FT			= $(addprefix $(LIB_DIR),libft.a)

# FILES
SRCS			= 	minishell \
					ft_parse \
					ft_get_cmd_lines \
					env \
					export \
					export2 \
					builtin \
					builtin2 \
					builtin3 \
					token \
					token2 \
					token3 \
					ft_init_signal \
					ft_redirection \
					ft_pipes \
					ft_exe_cmd \
					ft_error \

FILES			= $(addsuffix .c, $(SRCS))
OBJECTS			= $(addprefix $(BUILDING_DIR),$(FILES:.c=.o))

# BUILDING RULES
all:			objects ${LIB_FT} $(NAME)
				$(CC) $(C_FLAGS) ${OBJECTS} -o ${NAME} ${LIB_FT}

objects:		${LIB_FT}
				mkdir -p building_dir

$(BUILDING_DIR)%.o:$(SRCS_DIR)%.c
				$(CC) $(C_FLAGS) -I $(INCLUDES_DIR) -c $< -o $@

${LIB_FT}:
				make -C ${LIB_DIR}
${NAME}:		${OBJECTS}

# CLEANING RULES
clean:
				rm -f $(OBJECTS)
				make clean -C ${LIB_DIR}
				rm -Rf building_dir

fclean:			clean
				rm -f $(NAME)
				make fclean -C ${LIB_DIR}

re:				fclean all

# TESTING RULES
test:			all
				./${NAME}

.PHONY:			all clean fclean re
