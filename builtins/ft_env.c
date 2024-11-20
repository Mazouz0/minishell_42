/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:10:19 by zqouri            #+#    #+#             */
/*   Updated: 2024/10/27 02:39:52 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (cmd && !cmd->args[1])
	{
		while (tmp)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		return (0);
	}
	else
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		return (127);
	}
}
