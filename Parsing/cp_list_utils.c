/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:03:52 by mohmazou          #+#    #+#             */
/*   Updated: 2024/10/27 04:03:54 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_p_cmd	*ft_new_cp(char *cmd, int i, t_env *env_list)
{
	t_p_cmd	*new_cmd;

	new_cmd = (t_p_cmd *)ft_malloc(sizeof(t_p_cmd), 0);
	new_cmd->pipe_line = i;
	get_line(cmd, new_cmd, env_list);
	new_cmd->next = NULL;
	return (new_cmd);
}

void	cp_add_back(t_p_cmd **cp_list, t_p_cmd *new_cmd)
{
	t_p_cmd	*tmp;

	if (!(*cp_list))
	{
		(*cp_list) = new_cmd;
		return ;
	}
	tmp = (*cp_list);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
