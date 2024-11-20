/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:04:37 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/03 13:23:38 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_len(char *line, t_env *env)
{
	int		len;

	len = ft_strlen(line) + (c_ex(line) * ft_maxsize(env, 1));
	return (len);
}

void	*allocat_zero(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size, 0);
	ft_memset(ptr, 0, size);
	return (ptr);
}

int	ft_cnt_red(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			count++;
			if (line[i + 1] == c)
				i++;
		}
		i++;
	}
	return (count);
}

void	join_exit(char *new_line, int pipe_line, int *j, int *i)
{
	int		k;
	char	*str;

	if (pipe_line == 0)
		str = ft_itoa(exit_status(-1));
	else
		str = ft_itoa(0);
	k = 0;
	while (str[k])
	{
		new_line[*j] = str[k];
		(*j)++;
		k++;
	}
	new_line[*j] = '\0';
	(*i)++;
}
