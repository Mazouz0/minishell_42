/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:20:41 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:20:42 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error("fork failed: ");
		return (-1);
	}
	return (pid);
}

void	pid_waiting(int flag)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
		;
	// {
	// 	if (WIFEXITED(status))
	// 	{
	// 		exit_status(WEXITSTATUS(status));
	// 	}
	// 	else if (WIFSIGNALED(status))
	// 	{
	// 		if (WTERMSIG(status) == 2)
	// 		{
	// 			write(1, "\n", 1);
	// 			exit_status(130);
	// 		}
	// 		else if (WTERMSIG(status) == 3)
	// 		{
	// 			write(1, "Quit: 3\n", 8);
	// 			exit_status(131);
	// 		}
	// 	}
	// }
	if (flag)
		exit_status(1);
}

void	wait_status(int pid, int flag)
{
	int	status;

	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
		{
			exit_status(WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
			{
				write(1, "\n", 1);
				exit_status(130);
			}
			else if (WTERMSIG(status) == 3)
			{
				write(1, "Quit: 3\n", 8);
				exit_status(131);
			}
		}
	}
	if (flag)
		exit_status(1);
}

char	*get_last_arg(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	if (i == 0)
		return (NULL);
	return (ft_strdup_(args[i - 1]));
}

int	cmd_loop(t_cmd *cmd, t_env **env_list, int *fd, int *flag)
{
	if (cmd->next == NULL)
	{
		if (is_builtin(cmd) && cmd->pipe_line == 0)
			exit_status(ft_builtin(cmd, env_list));
		else if (process_child_end(cmd, env_list, flag) == -1)
			return (-1);
		return (-1);
	}
	if (process_child(cmd, env_list, fd, flag) == -1)
		return (-1);
	return (0);
}

void	ft_execut_cmd(t_cmd *cmd, t_env **env_list, int fd_in, int fd_out)
{
	int		fd[2];
	int		flag;
	char	*last_arg;

	flag = 0;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	while (cmd)
	{
		last_arg = get_last_arg(cmd->args);
		if (cmd_loop(cmd, env_list, fd, &flag) == -1)
			break ;
		cmd = cmd->next;
	}
	update_var(env_list, "_", last_arg, 0);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_fd(fd_in, fd_out);
	pid_waiting(flag);
}
