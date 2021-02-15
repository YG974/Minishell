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
					env2 \
					builtin \
					builtin2 \
					builtin3 \
					builtin4 \
					builtin5 \
					token \
					token2 \
					token3 \
					token4 \
					token5 \
					ft_init_signal \
					ft_redirection \
					ft_pipes \
					ft_exe_cmd \
					ft_error \
					ft_split_ms \

FILES			= $(addsuffix .c, $(SRCS))
OBJECTS			= $(addprefix $(BUILDING_DIR),$(FILES:.c=.o))

# BUILDING RULES
all:			objects ${LIB_FT} $(NAME)

objects:		${LIB_FT}

$(BUILDING_DIR)%.o:$(SRCS_DIR)%.c
				$(CC) $(C_FLAGS) -I $(INCLUDES_DIR) -c $< -o $@

${LIB_FT}:
				make -C ${LIB_DIR}
				mkdir -p building_dir
${NAME}:		${OBJECTS}
				$(CC) $(C_FLAGS) ${OBJECTS} -o ${NAME} ${LIB_FT}

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
