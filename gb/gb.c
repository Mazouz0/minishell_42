/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:20:53 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:20:54 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_list(t_garb *list)
{
	t_garb	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		free(tmp->addr);
		list = list->next;
		free(tmp);
	}
}

void	add_node(t_garb **list, t_garb *node)
{
	t_garb	*head;

	if (!list || !node)
		return ;
	head = *list;
	node->next = NULL;
	if (!head)
	{
		*list = node;
		return ;
	}
	while (head->next != NULL)
		head = head->next;
	head->next = node;
}

void	*gb_malloc(size_t size, int type)
{
	static t_garb	*list;
	t_garb			*node;
	void			*addr;

	if (type == 1)
		clear_list(list);
	else if (type == 0)
	{
		addr = malloc(size);
		node = malloc(sizeof(t_garb));
		if (!addr || !node)
		{
			clear_list(list);
			return (NULL);
		}
		node->addr = addr;
		add_node(&list, node);
		return (addr);
	}
	return (NULL);
}
