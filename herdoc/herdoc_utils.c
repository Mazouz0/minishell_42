/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:15:24 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/02 16:15:35 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	will_expd(char *del)
{
	while (*del)
	{
		if (*del == '\'' || *del == '\"')
			return (0);
		del ++;
	}
	return (1);
}

char	*gnrt_name(void)
{
	char		*file_name;
	static int	i;

	file_name = ft_strjoin("herdoc", ft_itoa(i++));
	return (file_name);
}

int	del_quote(int *sq, int *dq, char r)
{
	if (r == '\'' && !(*dq))
	{
		*sq = !(*sq);
		return (1);
	}
	if (r == '"' && !(*sq))
	{
		*dq = !(*dq);
		return (1);
	}
	return (0);
}

int	to_herdoc(char *redir)
{
	if (redir[0] == '<' && redir[1] == '<')
		return (1);
	return (0);
}

void	unlik_herdoc(char **redir, int sig_flag)
{
	int	i;

	if (sig_flag == -1337)
	{
		i = 0;
		while (redir[i])
			unlink(redir[i++]);
		if (sig_flag == -1337)
			exit_status(1);
		else
			exit_status(0);
	}
}
