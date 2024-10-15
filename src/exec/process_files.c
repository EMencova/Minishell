/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:25:13 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:17:57 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_output_redirection(t_exec *exec, char **args, int i, int append)
{
	if (!args[i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exec->out = -1;
		return (0);
	}
	exec->out = open_fd(exec->out, args[i + 1], 1, append);
	if (exec->out == -1)
	{
		perror("Error opening output file");
		return (0);
	}
	args[i] = NULL;
	args[i + 1] = NULL;
	return (1);
}

int	handle_input_redirection(t_exec *exec, char **args, int *i)
{
	if (!args[*i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exec->in = -1;
		return (0);
	}
	exec = infile_one(exec, args, i);
	if (exec->in == -1)
		return (0);
	return (5);
}

int	handle_here_document_redirection(t_exec *exec, char **args, int *i)
{
	if (!args[*i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exec->in = -1;
		return (0);
	}
	infile_two(exec, args, i);
	if (exec->in == -1)
		return (0);
	return (5);
}

int	parse_redir(t_exec *exec, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			return (handle_output_redirection(exec, args, i, 0));
		}
		else if (ft_strcmp(args[i], ">>") == 0)
		{
			return (handle_output_redirection(exec, args, i, 1));
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			return (handle_input_redirection(exec, args, &i));
		}
		else if (ft_strcmp(args[i], "<<") == 0)
		{
			return (handle_here_document_redirection(exec, args, &i));
		}
		i++;
	}
	return (0);
}
