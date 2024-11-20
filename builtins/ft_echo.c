/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:19:26 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:19:27 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] != '-')
		return (1);
	if (str[++i] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	i = 1;
	while (cmd->args[i] && !echo_option(cmd->args[i]))
	{
		n_flag++;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i ++], cmd->fd_out);
		if (cmd->args[i])
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (!n_flag)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
