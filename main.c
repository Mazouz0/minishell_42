/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:01:04 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/08 12:38:13 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(exit_status(-1));
	}
	if (line[0] == '\0' || all_space(line))
		return (1);
	if (!ft_check_syntax(line))
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		exit_status(258);
		return (1);
	}
	add_history(line);
	return (0);
}

int	ft_maxsize(t_env *env_list, int flag)
{
	t_env		*tmp;
	static int	i;

	if (flag == 0)
	{
		i = 0;
		tmp = env_list;
		while (tmp)
		{
			if ((int)ft_strlen(tmp->value) > i)
				i = ft_strlen(tmp->value);
			tmp = tmp->next;
		}
	}
	return (i);
}

void	start_loop(t_env *env_list, struct termios *term)
{
	char	*line;
	t_p_cmd	*cp_list;
	t_cmd	*cmd_list;

	line = NULL;
	while (1)
	{
		g_sig = 1;
		ft_handle_signals();
		ft_maxsize(env_list, 0);
		line = readline("minishell $> ");
		if (ft_add(line))
		{
			free(line);
			continue ;
		}
		ft_parsing(line, &cp_list, env_list);
		cmd_list = NULL;
		ft_merge(&cmd_list, cp_list, env_list);
		ft_execut_cmd(cmd_list, &env_list, 0, 0);
		free(line);
		if (g_sig)
			tcsetattr(STDIN_FILENO, TCSANOW, term);
		ft_malloc(0, 1);
	}
}

int	main(int ac, char **av, char **env)
{
	struct termios	term;
	t_env			*env_list;

	if (ac != 1 || av[1])
		return (write(2, "Error: no arguments needed\n", 27));
	if (!isatty(STDIN_FILENO))
	{
		printf("You should run minishell from a terminal file :\n");
		exit(1);
	}
	if (!env[0])
		env = empty_env();
	tcgetattr(STDIN_FILENO, &term);
	env_list = NULL;
	ft_env_list(&env_list, env, 0);
	shell_lvl(env_list);
	rl_catch_signals = 0;
	start_loop(env_list, &term);
	ft_lst_clear_env(&env_list);
	gb_malloc(0, 1);
	ft_malloc(0, 1);
	return (0);
}
