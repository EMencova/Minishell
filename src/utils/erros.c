/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfontene <yfontene@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:08:44 by yasmine           #+#    #+#             */
/*   Updated: 2024/09/09 14:46:28 by yfontene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error(char *description, int exit_code)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error\n", 6);
	if (description)
		write(2, description, ft_strlen(description));
	else
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	write(2, RST_COLOR, ft_strlen(RST_COLOR));
	if (exit_code == 1)
		exit(EXIT_FAILURE);
	return (errno);
}

/*void    error_file(char *file)
{
    ft_putstr_fd(RED, 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": No such file or directory", 2);
    ft_putstr_fd(RST_COLOR, 2);
}

void    error_no_such_file_(char *command)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": No such file or directory", 2);
	ft_putstr_fd(RST_COLOR, 2);
}*/

/*void    error_command(char *command)
{
    ft_putstr_fd(RED, 2);
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": command not found", 2);
    ft_putstr_fd(RST_COLOR, 2);
}

int			error_redirection(int file_type)
{
    if (!(file_type == FILE || file_type == -FILE
			|| file_type == HERE_DOC_END
			|| file_type == -HERE_DOC_END))
	{
		ft_error("No redirection File", 0);
		return (1);
	}
	return (0);
}*/
