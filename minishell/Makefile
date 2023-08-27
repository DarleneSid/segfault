NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c \
					ft_echo.c \
					ft_expand.c \
					parsing/ft_space.c \
					parsing/ft_syntax.c \
					parsing/ft_export.c \
					parsing/ft_unset.c \
					parsing/env.c \
					exec/error.c \
					exec/path.c \
					exec/exec.c \
					exec/parse_arr.c \
					exec/utils.c \
					builtin/ft_cd.c \
					builtin/ft_echo.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft/includes

LIB				=	-lreadline -lm -Llibft -lft

CC				=	cc

CDFLAGS 		= -MMD -MP

CFLAGS			=	-g3# -Wall -Werror -Wextra

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	make -C libft
	$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/exec
	mkdir -p objs/builtin

clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

leaks: ${NAME}
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

leask: $(NAME)
	clear && valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
# .SILENT:
