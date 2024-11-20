/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:56:27 by mohmazou          #+#    #+#             */
/*   Updated: 2024/10/27 21:41:00 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_expd(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '$')
		{
			buffer ++;
			if (*buffer != '$' && *buffer != '\'' && *buffer != '\"'
				&& *buffer != ' ')
				return (1);
		}
		buffer ++;
	}
	return (0);
}

t_utils	*ini_fil_u(int len_bfr)
{
	t_utils	*utils;

	utils = ft_malloc(sizeof(t_utils), 0);
	utils->i = 0;
	utils->j = 0;
	utils->len = len_bfr;
	utils->status = 0;
	return (utils);
}

int	fill_buffer(t_env *env, char *bfr, char *new_bf, int pipe_line)
{
	t_utils	*u;

	u = ini_fil_u(ft_strlen(bfr));
	while (u->i < u->len)
	{
		u->status = (bfr[u->i] == '$' && bfr[u->i + 1]);
		if (u->status && bfr[u->i + 1] != ' ' && bfr[u->i +1] != '\t')
			u->i++;
		if (u->status && bfr[u->i] == '?')
			join_exit(new_bf, pipe_line, &u->j, &u->i);
		else if (u->status && not_expandable(bfr[u->i]))
			u->i ++;
		else if (u->status && ft_to_ex(bfr[u->i]))
		{
			join_val(env, bfr + u->i, new_bf, &u->j);
			while (bfr[u->i] && ft_to_ex(bfr[u->i]))
				u->i ++;
		}
		else
			new_bf[u->j++] = bfr[u->i++];
	}
	return (0);
}

char	*expended_buffer(char *buffer, t_env *env, int pipe_line)
{
	char	*new_bf;
	int		len;

	if (!buffer || !should_expd(buffer))
		return (buffer);
	len = new_len(buffer, env);
	new_bf = allocat_zero(len + 1);
	if (fill_buffer(env, buffer, new_bf, pipe_line) == -1)
		return (NULL);
	return (new_bf);
}

t_utils	*init_herd_uti(void)
{
	t_utils	*utls;

	utls = ft_malloc(sizeof(t_utils), 0);
	utls->fd = 0;
	utls->i = 0;
	return (utls);
}
