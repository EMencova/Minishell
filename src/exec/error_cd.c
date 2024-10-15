/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:12:39 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 21:13:54 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../../minishell.h"
#include <dirent.h>

void	handle_cd_args(char **args)
{
	DIR	*dir;

	if (access(args[1], F_OK) == -1)
	{
		m_error(ERR_NEWDIR, args[1], 1);
		return ;
	}
	dir = opendir(args[1]);
	if (!dir)
	{
		if (errno == ENOTDIR)
			m_error(ERR_NOTDIR, args[1], 1);
		else
			m_error(ERR_NEWDIR, args[1], 1);
		return ;
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
	closedir(dir);
}

void	handle_cd_target_dir(char *target_dir)
{
	if (chdir(target_dir) == -1)
	{
		perror("cd");
		g_exit_status = 1;
	}
}

void	error_cd(char **args, char *target_dir)
{
	if (!args[1] && (!target_dir || target_dir[0] == '\0'))
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	if (args[1])
		handle_cd_args(args);
	else if (target_dir)
		handle_cd_target_dir(target_dir);
}
