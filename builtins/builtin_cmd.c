/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:18:54 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:19:06 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin(t_cmd *cmd, t_env **env_list)
{
	int	st;

	st = 0;
	if (!cmd || cmd->fd_in == -1 || cmd->fd_out == -1)
		return (1);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo")) == 0)
		st = ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen("cd")) == 0)
		st = ft_cd(cmd, *env_list, NULL, NULL);
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd")) == 0)
		st = (ft_pwd(*env_list));
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen("env")) == 0)
		st = (ft_env(cmd, *env_list));
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen("export")) == 0)
		st = ft_export(cmd, env_list);
	else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")))
		st = ft_exit(cmd);
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen("unset")) == 0)
		st = ft_unset(cmd, env_list);
	close_fd(cmd->fd_in, cmd->fd_out);
	return (st);
}

int	ft_export_error(char *name)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

void	print_list_declare(t_env **env)
{
	t_env	*current_env;
	t_env	*tmp;
	char	**envp;

	current_env = NULL;
	envp = sort_env(*env, count_env(*env));
	ft_env_list(&current_env, envp, 1);
	tmp = current_env;
	while (current_env)
	{
		if (ft_strcmp(current_env->name, "_") == 0)
		{
			current_env = current_env->next;
			continue ;
		}
		if (current_env->name && current_env->value)
			printf("declare -x %s=\"%s\"\n",
				current_env->name, current_env->value);
		else if (!current_env->value)
			printf("declare -x %s\n", current_env->name);
		current_env = current_env->next;
	}
	ft_lst_clear_env(&tmp);
}

char	*check_name_env(char *name)
{
	char	*new_name;
	char	*tmp;
	int		i;

	i = 0;
	if (!name)
		return (NULL);
	while (name[i])
	{
		if (name[i] == '+')
		{
			tmp = ft_substr_(name, 0, i);
			new_name = ft_strdup_(tmp);
			free(tmp);
			return (new_name);
		}
		i++;
	}
	return (ft_strdup_(name));
}

int	check_empty_value(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=' && var[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}
