/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 03:35:57 by zqouri            #+#    #+#             */
/*   Updated: 2024/11/06 11:13:30 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**empty_env(void)
{
	char	**env;
	char	*str;

	str = getcwd(NULL, 0);
	env = (char **)gb_malloc((sizeof(char *) * 5), 0);
	if (!env)
		return (NULL);
	env[0] = ft_strdup_("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[1] = ft_strjoin_("PWD=", str);
	env[2] = ft_strdup_("SHLVL=0");
	env[3] = ft_strdup_("_=/usr/bin/env");
	env[4] = NULL;
	free(str);
	return (env);
}

t_env	*ft_env_new_(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup_(key);
	new->value = ft_strdup_(value);
	new->next = NULL;
	return (new);
}

t_env	*ft_env_new(char *env)
{
	t_env	*new;
	char	*equal;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (!equal)
	{
		new->name = ft_strdup_(env);
		new->value = NULL;
	}
	else
	{
		new->name = ft_substr_(env, 0, equal - env);
		new->value = ft_strdup_(equal + 1);
	}
	new->next = NULL;
	return (new);
}

t_env	*find_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
