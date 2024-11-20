/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:39:48 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/02 12:20:24 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cp_arr(char **in_redir)
{
	int	i;

	i = 0;
	while (in_redir[i])
		i ++;
	return (i);
}

t_utils	*init_utils(char **redir)
{
	t_utils	*utils;

	utils = ft_malloc(sizeof(t_utils), 0);
	utils->fd = 0;
	utils->i = 0;
	utils->fds_tab = ft_malloc(sizeof(int) * cp_arr(redir), 0);
	utils->f_name = NULL;
	utils->flag = 1;
	return (utils);
}

char	*get_r_name(char *redir, t_env *env)
{
	int		i;

	(void)env;
	i = 0;
	if (redir[i] == '<' || redir[i] == '>')
		i++;
	if (redir[i] == '<' || redir[i] == '>')
		i++;
	while (redir[i] == ' ' || redir[i] == '\t')
		i++;
	return (redir + i);
}

void	open_red(t_p_cmd *cmd, int *fd_in, int *fd_out, t_env *env)
{
	t_utils	*u;
	char	**redir;

	redir = cmd->redir;
	u = init_utils(redir);
	while (redir && redir[u->i] && u->fd != -1)
	{
		u->f_name = get_r_name(redir[u->i], env);
		u->f_name = get_f_name(u->f_name, env, cmd->pipe_line);
		u->fd = err_get_name(&u, fd_in, fd_out);
		if (redir[u->i][0] == '>' && u->fd != -1)
			open_out(&u, redir[u->i], fd_out);
		if (redir[u->i][0] == '<' && u->fd != -1)
			open_in(&u, redir[u->i], fd_in);
		u->i ++;
	}
	close_tab(u->fds_tab, u->i, *fd_in, *fd_out);
	unlinker(redir, u->i, env);
}
