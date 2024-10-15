/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:33:25 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 20:37:10 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_cd_errors(char **args, char *target_dir)
{
	if (!target_dir)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
		return (1);
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

char	*get_target_directory(t_shell *shell, char **args, char *home_dir)
{
	if (!args[1] || ft_strcmp(args[1], "") == 0)
		return (ft_strdup(home_dir));
	else if (ft_strcmp(args[1], "-") == 0)
		return (get_env("OLDPWD", shell->keys, 6));
	return (ft_strdup(args[1]));
}

void	update_pwd_and_oldpwd(t_shell *shell)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 1024);
	if (current_dir)
	{
		set_env_ex(shell, "OLDPWD", current_dir);
		set_env_ex(shell, "PWD", current_dir);
		free(current_dir);
	}
}

int	m_cd(t_shell *shell)
{
	char	*home_dir;
	char	**args;
	char	*target_dir;

	g_exit_status = 0;
	home_dir = get_env("HOME", shell->keys, 4);
	args = ((t_exec *)shell->cmds->content)->args;
	if (!home_dir)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	target_dir = get_target_directory(shell, args, home_dir);
	if (handle_cd_errors(args, target_dir))
	{
		free(home_dir);
		return (g_exit_status);
	}
	error_cd(args, target_dir);
	if (!g_exit_status)
		update_pwd_and_oldpwd(shell);
	free(home_dir);
	free(target_dir);
	return (g_exit_status);
}
/*
int m_cd(t_shell *shell)
{
	char    **args;
    char    *home_dir;
    char    *current_dir;
    char    *target_dir;

    g_exit_status = 0;
    args = ((t_exec *)shell->cmds->content)->args;

    // Check for too many arguments
    if (args[1] && args[2])
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        g_exit_status = 1;
        return g_exit_status;
    }

    // Get HOME directory
    home_dir = get_env("HOME", shell->keys, 4);
    if (!home_dir)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        g_exit_status = 1;
        return g_exit_status;
    }

    // Determine target directory
    if (!args[1] || ft_strcmp(args[1], "") == 0)
        target_dir = ft_strdup(home_dir);
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_dir = get_env("OLDPWD", shell->keys, 6);
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            g_exit_status = 1;
            free(home_dir);
            return g_exit_status;
        }
    }
    else
        target_dir = ft_strdup(args[1]);

    // Perform error checking for changing directory
    error_cd(args, target_dir);
    
    // If no error occurred, update PWD and OLDPWD
    if (!g_exit_status)
    {
        current_dir = getcwd(NULL, 1024);
        if (current_dir)
        {
            set_env_ex(shell, "OLDPWD", current_dir);  // Use set_env_ex
            set_env_ex(shell, "PWD", current_dir);     // Use set_env_ex
            free(current_dir);
        }
    }

    // Clean up
    free(home_dir);
    free(target_dir);
    return g_exit_status;
}*/
