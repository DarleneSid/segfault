LIBFT			=	libft.a
SRCS_NAMES		=	main.c \
					ft_expand.c \
					parsing/ft_space.c \
					parsing/ft_syntax.c \
					parsing/ft_export.c \
					parsing/ft_unset.c \
					parsing/env.c \
					exec/path.c \
					exec/parse_arr.c \
SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))
OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))
LIB				=	-lreadline -lm -Llibft -lft
CFLAGS			=	-g3 -Wall -Werror -Wextra
all:	${NAME}
	make -C libft
	mkdir -p objs/parsing
clean:
	make clean -C libft
fclean:	clean
	make fclean -C libft
leaks: ${NAME}
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell
leask: $(NAME)
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell
re:	fclean all
.PHONY:	all clean fclean re bonus leaks stop
