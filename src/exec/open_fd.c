/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emencova <emencova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:13:13 by emencova          #+#    #+#             */
/*   Updated: 2024/10/08 22:14:39 by emencova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_str_is_space(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	char_count(char *str, char c)
{
	int	nbr;

	if (!str)
		return (0);
	nbr = 0;
	while (*str)
	{
		if (*str == c)
			nbr++;
		str++;
	}
	return (nbr);
}

int	m_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 1024);
	if (!buffer)
	{
		perror("pwd\n");
		return (1);
	}
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}

int	check_file_permissions(char *path, int is_output)
{
	if (!is_output && access(path, F_OK) == -1)
		return (m_error(ERR_NEWDIR, path, 126), -1);
	if (!is_output && access(path, R_OK) == -1)
		return (m_error(ERR_NWPERM, path, 126), -1);
	if (is_output && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		return (m_error(ERR_NWPERM, path, 126), -1);
	return (0);
}

int	open_fd(int fd, char *path, int is_output, int append)
{
	if (fd > 2)
		close(fd);
	if (!path || check_file_permissions(path, is_output) == -1)
	{
		fprintf(stderr, "Error: Invalid path\n");
		return (-1);
	}
	if (is_output)
	{
		if (append)
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}
