/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:44:31 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/08 10:55:51 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	err_get_name(t_utils **u, int *fd_in, int *fd_out)
{
	if (!(*u)->f_name)
	{
		*fd_in = -1;
		*fd_out = -1;
		exit_status(1);
		(*u)->fds_tab[(*u)->i] = -1;
		return (-1);
	}
	return (1);
}

void	open_out(t_utils **u, char *red, int *fd_out)
{
	if (red[1] == '>')
		(*u)->fd = open((*u)->f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		(*u)->fd = open((*u)->f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*fd_out = (*u)->fd;
	(*u)->fds_tab[(*u)->i] = (*u)->fd;
	if ((*u)->fd == -1)
	{
		ft_putstr_fd("minishell: Permission denied\n", STDERR_FILENO);
		exit_status(1);
	}
}

void	open_in(t_utils **u, char *redir, int *fd_in)
{
	int	fd;

	if (redir[1] == '<')
	{
		fd = open((*u)->f_name, O_RDONLY);
		if (fd != -1)
			*fd_in = fd;
		unlink((*u)->f_name);
		(*u)->fds_tab[(*u)->i] = *fd_in;
	}
	else
	{
		(*u)->fd = open((*u)->f_name, O_RDONLY);
		*fd_in = (*u)->fd;
		(*u)->fds_tab[(*u)->i] = (*u)->fd;
	}
	if ((*u)->fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((*u)->f_name, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit_status(1);
	}
}

void	unlinker(char **redir, int i, t_env *env)
{
	char	*f_name;

	while (redir && redir[i])
	{
		if (redir[i][0] == '<' && redir[i][1] == '<')
		{
			f_name = get_r_name(redir[i], env);
			f_name = get_f_name(f_name, env, 1);
			unlink(f_name);
		}
		i ++;
	}
}
