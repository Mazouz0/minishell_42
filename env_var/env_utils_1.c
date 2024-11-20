/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:19:51 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:19:52 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_env(t_env *env_list, char *name, char *value)
{
	t_env	*tmp;

	tmp = env_list;
	if (!name || !value)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup_(value);
			return ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = ft_env_new_(name, value);
		ft_env_add_back(&env_list, tmp);
	}
}

char	*ft_env_search(t_env *env_list, char *name)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_lstlast_env(t_env *env)
{
	t_env	*last;

	if (!env)
		return (NULL);
	last = env;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!env || !new)
		return ;
	if (*env)
	{
		last = ft_lstlast_env(*env);
		if (!last)
			return ;
		last->next = new;
	}
	else
		(*env) = new;
}

void	ft_env_list(t_env **env_list, char **env, int flag)
{
	int		i;
	t_env	*new;

	i = 0;
	new = NULL;
	if (!env)
		return ;
	while (env[i] && flag)
	{
		new = ft_env_new(env[i++]);
		if (!new)
			ft_error("error: failed");
		ft_env_add_back(env_list, new);
	}
	while (env[i] && !flag)
	{
		if (ft_strncmp(env[i], "OLDPWD", 6) != 0)
		{
			new = ft_env_new(env[i]);
			if (!new)
				ft_error("error: failed");
			ft_env_add_back(env_list, new);
		}
		i++;
	}
}
