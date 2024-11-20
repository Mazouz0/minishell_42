/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:45:21 by zqouri            #+#    #+#             */
/*   Updated: 2024/10/27 02:45:24 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(path);
	}
	else if (ft_env_search(env, "PWD"))
	{
		ft_putstr_fd(ft_env_search(env, "PWD"), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (ft_env_search(env, "OLDPWD"))
	{
		ft_putstr_fd(ft_env_search(env, "OLDPWD"), STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("minishell: pwd:", STDERR_FILENO);
	return (0);
}
