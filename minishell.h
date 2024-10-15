/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:48:13 by yasmine           #+#    #+#             */
/*   Updated: 2024/10/09 09:53:48 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define GREEN      "\033[0;32m"
# define RED        "\033[0;31m"
# define YELLOW	    "\033[0;33m"
# define MAGENTA	"\033[0;35m"
# define CYAN       "\033[0;36m"
# define RST_COLOR  "\033[0m"

# define STDIN  0
# define STDOUT 1
# define STDERR 2

# define MAX_PATH 4096

# define CMD 3
# define ARG 4      
# define REDIR_OUT_SUBS 5
# define REDIR_OUT_ATTACH 6
# define REDIR_IN 7
# define REDIR_DOC 8
# define FILE 9
# define ERROR 10
# define PROTECTED_DOLLAR 11
# define PROTECTED_QUOTE 12
# define SKIPED_COMMAND	13
# define HERE_DOC 14
# define HERE_DOC_END 15

typedef struct s_env
{
	char				**env;
	char				**sorted;
	int					exit_status;
}						t_env;

typedef struct s_tokens
{
	int					nbr;
	int					pipe;
	int					*type;
	char				**tokens;
}						t_tokens;

extern int					g_exit_status;

typedef struct s_shell
{
	t_list	*cmds;
	char	**keys;
	pid_t	mpid;
}		t_shell;

//UTILS
int			absolute_value(int nb);
int			count(char **str);
int			max_of(int i, int j);
int			ft_error(char *description, int exit_code);
void		free_str_array(char **arr);
void		error_file(char *file);
int			error_redirection(int file_type);
void		error_no_such_file(char *command);
void		error_command(char *command);
char		*ft_stringjoin(char *str, char c);
char		*extract_substring(char const *s, unsigned int start, size_t len);
void		join_backslash(char **path);
char		*format_var(char *var, char *value);
void		new_var(char *var, char *value, t_shell *shell);
void		update_env(char *var, char *value, t_shell *shell);
void		append_to_env(char *variable, char *value, int size,
				t_shell *shell);
char		*set_dollar(char *str, int i, t_shell *shell);
int			len_dollar(char *str, int i);
char		**dup_array(char **env);
void		sort_array(char **sorted);
void		env_init(char **env, t_shell *shell);
int			count_backslash(char *line, int i);
int			valid_backslash(char **tokens);
void		free_tokens(t_tokens *token);
void		free_dollar(char **original, char **replacement);
void		free_split(char **split);
int			syntax_redirections(t_tokens *tokens);
int			syntax_grammar(char **commands, t_tokens *tokens);
int			count_separator(char *line, char separator);
int			str_isdigit(char *str);
char		**separator_split(char *line, int *separatorI, int nbr_separator);
char		**token_split(char *line, int nbr);
int			get_token_type(char *content, int len);
void		set_token_aux(int i, int *cmd, int *type);
void		set_tokens_type(int *type, char **content);
int			*set_token(t_tokens token);
int			skip_space(char *line, int i);
int			get_end(char *line, int i);
int			count_token(char *line);
int			is_empty(char *str);
int			is_protected(int type);
int			is_cmd(int type);
int			is_arg(int type);
int			is_redirection(int type);
void		env_update(char *env, char *new_value, t_shell *shell);
void		replace_value(int i, char *new_value, int len, char **arr);
char		*assemble_argument(char **args, int *token_class, int i);
int			get_next_positive(char **args, int *token_class, int i);
char		**join_args(char **args, int *token_class);
char		**arg_add(char *arg, char **arr);
void		print_invalid_identifier_error(char **args);
int			is_invalid_identifier(char *arg);
char		**update_or_add_env_var(char *variable, char *value,
				t_shell *shell);

//PARSING
char		*find_env_value(char *str, int i, char **sorted);
void		process_pipeline(char *line, t_shell *shell);
void		process_command_line(char *line, t_shell *shell);
void		dollar_replace(char **token, int i, t_shell *shell);
char		**dollar_spaces_split(char **old, int i);
void		arg_type(t_tokens *token, int oldsize, int newsize, int i);
char		*dollar_config(char *str, int pos, t_shell *shell);
int			dollar_presence(char *str);
char		*process_quotes(char *str, t_shell *shell);
char		*quotes_expand(char *content, int i, t_shell *shell);
t_tokens	process_quotes_tokens(t_tokens tokens, t_shell *shell);
void		exec_process_quotes(t_tokens *tokens, t_shell *shell);
void		type_of_separator(int *type_of, char **token);
void		filler_stokens(char **cmds, t_tokens **token, int nbr,
				t_shell *shell);
char		**split_pipes(char *line);
void		tokenize_commands(char **cmds, t_list **command_list,
				t_shell *shell);
int			token_dollar_end(char *str, int i);
int			token_word_end(char *str, int i);
int			token_quotes_end(char *str, int i);
int			token_redir_end(char *str, int i);
char		*parse_next_token(char *line, int reset, int keep_quotes);
bool		valid_quotes(const char *str);
void		initialize_token(char **cmds, t_tokens **token, int i, int nbr);
char		*expand_variable(char *original_token, int *k, t_shell *shell);
char		*process_expansion(char *original_token, t_shell *shell);
void		process_token(t_tokens *token, int i, int j, t_shell *shell);
void		combine_tokens(t_tokens *token, int i, int j);
int			check_unclosed_quotes(char *str);
void		handle_quotes(char current_char, bool *in_quotes, char *quote_type);
bool		is_pipe(char current_char, bool in_quotes);
bool		is_quote(char c);
bool		is_double_redirect(char *line, int i);
int			handle_tquotes(char *line, int i);
int			handle_token(char *line, int i);
char		**duplicate_and_sort_keys(char **keys);
void		populate_keys(char **env, t_shell *shell);
char		**allocate_keys(int env_size);
int			get_env_size(char **env);
void		sigint_handler(int sig);
void		cleanup_shell(t_shell *shell);
void		handle_quote_state(char c, bool *in_quotes, char *quote_type);
int			count_token(char *line);

#endif
