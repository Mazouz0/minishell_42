/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:39:31 by mohmazou          #+#    #+#             */
/*   Updated: 2024/10/27 06:39:32 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_merge(t_cmd **cmd_list, t_p_cmd *cp_list, t_env *env_list)
{
	t_cmd	*new_cmd;

	if (!cp_list)
		return ;
	while (cp_list)
	{
		new_cmd = ft_new_cmd(cp_list, env_list);
		cmd_add_back(cmd_list, new_cmd);
		cp_list = cp_list->next;
	}
}
