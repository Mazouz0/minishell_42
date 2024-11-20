/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:39:21 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/08 10:56:39 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_qot(char *str, int s_q, int d_q)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)ft_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	ft_bzero(new_str, ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' && !d_q)
		{
			s_q = !s_q;
			i++;
		}
		else if (str[i] == '\"' && !s_q)
		{
			d_q = !d_q;
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**ft_quoted_cmd(char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		tmp = rm_qot(cmd[i], 0, 0);
		cmd[i] = tmp;
		i++;
	}
	return (cmd);
}

t_cmd	*ft_new_cmd(t_p_cmd *cp_cmd, t_env *env_list)
{
	t_cmd	*new_cmd;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), 0);
	new_cmd->pipe_line = cp_cmd->pipe_line;
	new_cmd->args = ft_quoted_cmd(cp_cmd->cmd);
	if (cp_cmd->redir)
		open_red(cp_cmd, &fd_in, &fd_out, env_list);
	new_cmd->fd_in = fd_in;
	new_cmd->fd_out = fd_out;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *cmd_list;
	if (!tmp)
	{
		*cmd_list = new_cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	close_tab(int *fd_tab, int size, int in, int out)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fd_tab[i] != in && fd_tab[i] != out
			&& fd_tab[i] != 0 && fd_tab[i] != 1)
			close(fd_tab[i]);
		i++;
	}
}
