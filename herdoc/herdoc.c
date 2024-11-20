/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:21:25 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/02 16:17:38 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_del(char *redir)
{
	int		i;
	int		j;
	char	*del;
	int		sq;
	int		dq;

	i = 2;
	j = 0;
	sq = 0;
	dq = 0;
	while (redir[i] && ft_isspace(redir[i]))
		i++;
	del = ft_malloc(ft_strlen(redir) - i + 1, 0);
	while (redir[i])
	{
		i += del_quote(&sq, &dq, redir[i]);
		if (!sq && !dq && redir[i] == '$'
			&& (redir[i + 1] == '\'' || redir[i + 1] == '"'))
			i++;
		i += del_quote(&sq, &dq, redir[i]);
		if (redir[i])
			del[j ++] = redir[i ++];
	}
	del[j] = '\0';
	return (del);
}

int	buf_breaker(char *line, int *s, char *del)
{
	if (!line)
	{
		if (exit_status(-1) == -1337)
			*s = -1337;
		else
			*s = -42;
		rl_replace_line("", 0);
		return (-1);
	}
	if (ft_strcmp(line, del) == 0)
	{
		free(line);
		return (-1);
	}
	return (1);
}

char	*get_buf(int *s, char *red, int pipe_line, t_env *env)
{
	char	*line;
	char	*buffer;
	char	*del;
	int		expd;
	int		fd_dup;

	del = get_del(red);
	expd = will_expd(red);
	buffer = NULL;
	fd_dup = dup(STDIN_FILENO);
	while (1)
	{
		signal(SIGINT, ft_sig_herdoc);
		line = readline("> ");
		if (buf_breaker(line, s, del) == -1)
			break ;
		buffer = ft_strjoin(buffer, line);
		buffer = ft_strjoin(buffer, "\n");
		free(line);
	}
	dup2(fd_dup, STDIN_FILENO);
	close(fd_dup);
	if (expd)
		return (expended_buffer(buffer, env, pipe_line));
	return (buffer);
}

void	herdoc_hundeler(t_p_cmd **cmd, t_env *env, int *sg)
{
	t_utils	*u;
	char	*file_name;
	char	**file_tab;
	char	*buffer;

	file_tab = ft_malloc(sizeof(char *) * (cp_arr((*cmd)->redir) + 1), 0);
	u = init_herd_uti();
	if (!(*cmd) || !(*cmd)->redir)
		return ;
	while ((*cmd)->redir[u->i] && *sg != -1337)
	{
		if (to_herdoc((*cmd)->redir[u->i]))
		{
			file_name = gnrt_name();
			buffer = get_buf(sg, (*cmd)->redir[u->i], (*cmd)->pipe_line, env);
			u->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			file_tab[u->i] = file_name;
			write(u->fd, buffer, ft_strlen(buffer));
			close(u->fd);
			(*cmd)->redir[u->i] = ft_strjoin("<<", file_name);
		}
		u->i ++;
	}
	file_tab[u->i] = NULL;
	unlik_herdoc(file_tab, *sg);
}
