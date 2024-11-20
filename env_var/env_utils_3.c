/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:45:31 by zqouri            #+#    #+#             */
/*   Updated: 2024/10/27 03:39:16 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**sort_env(t_env *env, int n)
{
	char	**envp;
	int		swapped;
	int		i;
	int		j;

	envp = ft_get_envp(env);
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		swapped = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				swap(&envp[j], &envp[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
	return (envp);
}
