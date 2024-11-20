/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqouri <zqouri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:38:28 by zqouri            #+#    #+#             */
/*   Updated: 2024/11/06 11:08:19 by zqouri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_var(char *var, int flag)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if ((i == 0 && ft_isdigit(var[i]) && var[i] != '_') || var[0] == '+')
			return (0);
		if (var[i] == '+' && var[i + 1] != '\0')
		{
			if (flag == 0)
			{
				if (var[i + 1] == '=')
					return (i + 1);
			}
			else if (flag == 1)
				return (-1);
		}
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*new_value(char *var_value, char *value, int flag)
{
	char	*tmp;

	if (flag == 0)
	{
		free(var_value);
		return (ft_strdup_(value));
	}
	else
	{
		tmp = ft_strdup_(var_value);
		free(var_value);
		return (ft_strjoin_(tmp, value));
	}
}

void	update_var(t_env **env, char *name, char *value, int flag)
{
	t_env	*var;

	var = find_env(*env, name);
	if (!var)
	{
		var = ft_env_new_(name, value);
		ft_env_add_back(env, var);
		return ;
	}
	if (var->name && var->value && !value)
		return ;
	if (var->value && value)
		var->value = new_value(var->value, value, flag);
	else
		var->value = ft_strdup_(value);
}

void	add_var_env(char *var, t_env **env)
{
	int		size_name;
	int		size_value;
	char	*name;
	char	*value;
	char	*tmp;

	size_name = check_env_var(var, 0);
	if (!size_name)
		return ;
	tmp = ft_substr_(var, 0, size_name);
	name = check_name_env(tmp);
	size_value = size_name;
	while (var[size_name] == '=' && var[size_value])
		size_value++;
	value = ft_substr_(var, size_name + 1, size_value);
	if (ft_strlen(value) == 0)
		value = NULL;
	if (!check_empty_value(var))
		value = "";
	if (check_env_var(var, 1) == -1)
		update_var(env, name, value, 1);
	else
		update_var(env, name, value, 0);
}

int	ft_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!cmd->args[1])
	{
		print_list_declare(env);
		return (0);
	}
	while (cmd->args[i])
	{
		if (!check_env_var(cmd->args[i], 0))
			status = ft_export_error(cmd->args[i]);
		else
			add_var_env(cmd->args[i], env);
		i++;
	}
	return (status);
}
