/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:04:08 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/06 02:24:54 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_expandable(char *line, int i, int *dq)
{
	static int	inside_dq;
	static int	inside_sq;

	if (line[i] == '\'' && !inside_dq)
		inside_sq = !inside_sq;
	if (line[i] == '\"' && !inside_sq)
		inside_dq = !inside_dq;
	*dq = inside_dq;
	return (line[i] == '$' && !inside_sq);
}

char	*ft_get_name(char *str, int i)
{
	char	*name;
	int		j;

	j = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i ++;
	name = ft_substr(str, j, i - j);
	return (name);
}

int	c_ex(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && (ft_to_ex(str[i + 1]) || str[i + 1] == '?'
				|| str[i + 1] == '\'' || str[i + 1] == '\"'))
			count ++;
		i ++;
	}
	return (count);
}

int	not_expandable(char c)
{
	return ((c >= '0' && c <= '9') || c == '@');
}

int	ft_to_ex(char c)
{
	return (ft_isalnum(c) || c == '_');
}
