/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:03:40 by mohmazou          #+#    #+#             */
/*   Updated: 2024/10/27 04:03:42 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quote(char *line)
{
	int	quote;
	int	dquote;
	int	bracket;
	int	i;

	quote = 0;
	dquote = 0;
	bracket = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && dquote == 0)
			quote = !quote;
		if (line[i] == '\"' && quote == 0)
			dquote = !dquote;
		if (line[i] == '(' && quote == 0 && dquote == 0)
			bracket++;
		if (line[i] == ')' && quote == 0 && dquote == 0)
			bracket--;
		i++;
	}
	return ((quote || dquote || bracket));
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_ds_q(char c, int *dquote, int *s_quote)
{
	if (c == '\'' && (*dquote) == 0)
		*s_quote = !(*s_quote);
	if (c == '"' && (*s_quote) == 0)
		*dquote = !(*dquote);
	return (!(*dquote) && !(*s_quote));
}

static int	check_multi_pipe(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (s[i] == '|')
		return (1);
	while (s[i])
	{
		ft_ds_q(s[i], &double_quote, &single_quote);
		if (s[i] == '|' && !double_quote && !single_quote)
		{
			i ++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			if (s[i] == '|' || !s[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_syntax(char *line)
{
	line = ft_strtrim(line, " ");
	line = ft_strtrim(line, "\t");
	if (ft_check_quote(line))
		return (0);
	if (ft_check_direction(line))
		return (0);
	if (check_multi_pipe(line))
		return (0);
	return (1);
}
