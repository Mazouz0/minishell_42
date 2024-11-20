/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:06:35 by mohmazou          #+#    #+#             */
/*   Updated: 2024/10/31 02:07:14 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_qote(int *sq, int *dq, char c)
{
	if (c == '\'' && !(*dq))
		*sq = !(*sq);
	if (c == '\"' && !(*sq))
		*dq = !(*dq);
}

char	**get_rd(char *line, int dq, int sq)
{
	char	**rd;
	int		i;
	int		j;
	int		count;

	count = ft_cnt_red(line, '<') + ft_cnt_red(line, '>');
	rd = (char **)ft_malloc(sizeof(char *) * (count + 1), 0);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && !dq)
			sq = !sq;
		if (line[i] == '\"' && !sq)
			dq = !dq;
		if ((line[i] == '<' || line[i] == '>') && !dq && !sq)
		{
			rd[j] = get_redir(line, i);
			j++;
			if (line[i + 1] == '<' || line[i + 1] == '>')
				i++;
		}
	}
	rd[j] = NULL;
	return (rd);
}

int	to_expand(char *line)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !dq)
			sq = !sq;
		if (line[i] == '\"' && !sq)
			dq = !dq;
		if (line[i] == '$' && !sq)
			return (1);
		i++;
	}
	return (0);
}

char	*get_redir(char *line, int i)
{
	char	*redir;
	int		j;
	int		dq;
	int		sq;

	j = i;
	dq = 0;
	sq = 0;
	while (line[j] && (line[j] == '>' || line[j] == '<'))
		j++;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	while (line[j])
	{
		if (line[j] == '\'' && !dq)
			sq = !sq;
		if (line[j] == '\"' && !sq)
			dq = !dq;
		if ((line[j] == ' ' || line[j] == '\t'
				|| line[j] == '>' || line[j] == '<') && !dq && !sq)
			break ;
		j++;
	}
	redir = ft_substr(line, i, j - i);
	return (redir);
}

int	to_break(char l)
{
	return (l == ' ' || l == '\t' || l == '<' || l == '>');
}
