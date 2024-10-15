# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eliskam <eliskam@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 11:06:25 by yasmine           #+#    #+#              #
#    Updated: 2024/10/08 16:19:47 by eliskam          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN				=	\033[0;32m
RED					=	\033[0;31m
YELLOW				=	\033[0;33m
MAGENTA				=	\033[0;35m
CYAN				=	\033[0;36m
END					=	\033[0m


NAME = minishell
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
LDFLAGS = -L./libft -lft -lreadline
RM = rm -f

PARSER_SRCS=			./src/parser/env_variable.c\
						./src/parser/p_dollar.c\
						./src/parser/p_token.c\
						./src/parser/p_quote.c\
						./src/parser/p_token_set.c\
						./src/parser/p_token_filler.c\
						./src/parser/p_token_filler_aux.c\
						main_helper.c\
						main.c\
						
UTILS_SRCS=				./src/utils/backslash.c\
						./src/utils/dollar.c\
						./src/utils/environment.c\
						./src/utils/erros.c\
						./src/utils/free.c\
						./src/utils/math.c\
						./src/utils/strings_handling.c\
						./src/utils/syntax_check.c\
						./src/utils/token_handling.c\
						./src/utils/token_utils.c\
						./src/utils/type_bool.c\
						./src/utils/token_set_utils.c\
						./src/utils/token_helper.c\
						./src/utils/env.c\
						./src/utils/token_utils_helper.c\
						./src/exec/builtin.c\
						./src/exec/cmds.c\
						./src/exec/get_next_line.c\
						./src/exec/get_next_line_utils.c\
						./src/exec/error.c\
						./src/exec/exec.c\
						./src/exec/exit.c\
						./src/exec/m_env_unset.c\
						./src/exec/process_files.c\
						./src/exec/get_files.c\
						./src/exec/utils_builtin.c\
						./src/exec/utils_form.c\
						./src/exec/env.c\
						./src/exec/m_echo.c\
						./src/exec/m_export_expr.c\
						./src/exec/tokenize_utils.c\
						./src/exec/tokenize.c\
						./src/exec/cmd_pipe.c\
						./src/exec/cmd_single.c\
						./src/exec/cmd_redir.c\
						./src/exec/cmd_redir_left.c\
						./src/exec/error_cd.c\
						./src/exec/checks.c\
						./src/exec/cd.c\
						./src/exec/open_fd.c\
						./src/exec/export_utils.c\
						./src/exec/heredocs.c\
						./src/exec/m_expr.c\
						./src/exec/extend_form.c\
			

SRCS=					$(UTILS_SRCS)\
						$(PARSER_SRCS)

OBJS=					$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) 
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
