/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:23:23 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:55:26 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_exec	*outfile_one(t_exec *node, char **ags, int *len)
{
	char	*error_msg;

	error_msg = "syntax error";
	(*len)++;
	if (ags[*len])
	{
		node->out = open_fd(node->out, ags[*len], 1, 0);
		if (node->out == -1)
		{
			ft_putendl_fd(error_msg, 2);
			g_exit_status = 1;
			*len = -1;
			return (node);
		}
	}
	else
	{
		ft_putendl_fd(error_msg, 2);
		g_exit_status = 2;
		*len = -1;
	}
	return (node);
}

t_exec	*outfile_two(t_exec *node, char **ags, int *len)
{
	char	*new_line;

	new_line = "syntax error";
	(*len)++;
	if (ags[*len])
		node->out = open_fd(node->out, ags[*len], 1, 1);
	if (!ags[*len] || node->out == -1)
	{
		*len = -1;
		ft_putendl_fd(new_line, 2);
		g_exit_status = 2;
	}
	return (node);
}

t_exec	*infile_one(t_exec *node, char **args, int *i)
{
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[*i])
		node->in = open_fd(node->in, args[*i], flags[0], flags[1]);
	if (!args[*i] || node->in == -1)
	{
		*i = -1;
		if (node->in != -1)
		{
			ft_putendl_fd(nl, 2);
			g_exit_status = 2;
		}
		else
			g_exit_status = 1;
	}
	return (node);
}

static void	assign_here_document_values(char **input, char **deli, \
		char **ags, int *len)
{
	input[0] = NULL;
	input[1] = NULL;
	deli[0] = ags[*len];
	deli[1] = "warning: here-document delimited by end-of-file";
}

void	infile_two(t_exec *node, char **ags, int *len)
{
	char	*input[2];
	char	*deli[2];

	assign_here_document_values(input, deli, ags, len);
	(*len)++;
	if (ags[*len])
	{
		deli[0] = ags[*len];
		node->in = create_here_document_fd(input, deli);
		if (node->in == -1)
		{
			g_exit_status = 0;
			*len = -1;
			return ;
		}
		return ;
	}
	if (!ags[*len] || node->in == -1)
	{
		*len = -1;
		if (node->in != -1)
			g_exit_status = 2;
	}
}
