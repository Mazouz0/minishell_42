/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:21:08 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:21:09 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *str)
{
	perror(str);
}

int	is_redir(const char *path)
{
	struct stat	statbuf;

	if ((stat(path, &statbuf) == 0)
		&& ((path[0] == '.' && path[1] == '/') || path[0] == '/'))
	{
		if (S_ISDIR(statbuf.st_mode))
			return (1);
		else if (S_ISREG(statbuf.st_mode))
			return (2);
	}
	return (0);
}

int	exec_permission(char *str)
{
	struct stat	statbuf;

	if (stat(str, &statbuf) == 0)
		if (statbuf.st_mode & S_IXUSR)
			return (0);
	return (1);
}

void	ft_execution_error(char *str)
{
	int	is_red;
	int	ex_perm;

	if (!str)
		return ;
	is_red = is_redir(str);
	ex_perm = exec_permission(str);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (is_red == 1)
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	else if (is_red == 2)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (is_red)
		exit(126);
	exit(127);
}
