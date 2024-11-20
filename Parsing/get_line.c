/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:06:57 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/01 03:22:42 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_utils	*ini_utls(char *line)
{
	t_utils	*u;

	u = (t_utils *)ft_malloc(sizeof(t_utils), 0);
	u->new_line = (char *)ft_malloc(sizeof(char) * (ft_strlen(line) + 1), 0);
	ft_bzero(u->new_line, ft_strlen(line) + 1);
	u->sq = 0;
	u->dq = 0;
	u->flag = 1;
	return (u);
}

void	skip(char *line, int *i)
{
	if (line[(*i)] == '<' || line[(*i)] == '>')
		(*i)++;
	while (line[(*i)] && (line[(*i)] == ' ' || line[(*i)] == '\t'))
		(*i)++;
}

void	copy_line(char l, char *c, int q)
{
	if (l == '\t' && q)
		*c = ' ';
	else
		*c = l;
}

char	*line_no_rd(char *line, int i, int j)
{
	t_utils	*u;

	u = ini_utls(line);
	while (line[i])
	{
		in_qote(&u->sq, &u->dq, line[i]);
		if ((line[i] == '<' || line[i] == '>') && !u->dq && !u->sq)
		{
			i ++;
			skip(line, &i);
			while (line[i])
			{
				in_qote(&u->sq, &u->dq, line[i]);
				if (line[i] && to_break(line[i]) && !u->dq && !u->sq)
					break ;
				i++;
			}
		}
		else
			copy_line(line[i++], u->new_line + j++, (!u->dq && !u->sq));
	}
	u->new_line[j] = '\0';
	return (u->new_line);
}

void	get_line(char *line, t_p_cmd *cp_list, t_env *env_list)
{
	char	*new_line;
	char	**rd;

	new_line = NULL;
	rd = get_rd(line, 0, 0);
	new_line = line_no_rd(line, 0, 0);
	if (to_expand(new_line))
		new_line = expd_line(new_line, env_list, cp_list->pipe_line);
	cp_list->line = new_line;
	cp_list->redir = rd;
	cp_list->cmd = ft_split_cmd(new_line, ' ', 0, 0);
}
