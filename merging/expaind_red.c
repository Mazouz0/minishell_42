/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaind_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:39:00 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/01 02:02:32 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expd_rd(char *f_name, t_env *env, int pipe_line)
{
	char	*new_name;

	new_name = expd_line(f_name, env, pipe_line);
	if (cnt_split(new_name, ' ', '\t', 0) != 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(new_name, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		return (NULL);
	}
	return (new_name);
}

char	*get_f_name(char *f_name, t_env *env, int pipe_line)
{
	char	*new_name;

	new_name = f_name;
	if (to_expand(new_name))
		new_name = expd_rd(new_name, env, pipe_line);
	if (!new_name)
		return (NULL);
	if (!ft_strcmp(rm_qot(new_name, 0, 0), "\0"))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(rm_qot(new_name, 0, 0), STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (NULL);
	}
	return (rm_qot(new_name, 0, 0));
}
