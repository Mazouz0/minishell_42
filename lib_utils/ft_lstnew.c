/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 03:22:23 by zqouri            #+#    #+#             */
/*   Updated: 2024/10/27 03:22:24 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnew_cmd(char *cmd)
{
	t_cmd	*new;
	char	**args;

	new = (t_cmd *)ft_malloc(sizeof(t_cmd), 0);
	args = ft_split(cmd, ' ');
	new->args = args;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new)
{
	t_cmd	*last;

	if (!cmd_list || !new)
		return ;
	if (*cmd_list)
	{
		last = ft_lstlast(*cmd_list);
		if (!last)
			return ;
		last->next = new;
	}
	else
		(*cmd_list) = new;
}
