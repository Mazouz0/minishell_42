/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:22:23 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/20 14:22:23 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>

# define NUM_BUILTINS 8

int		g_sig;

// garbage ----------------------
typedef struct s_garb
{
	void			*addr;
	struct s_garb	*next;
}	t_garb;

void	clear_list(t_garb *list);
void	add_node(t_garb **list, t_garb *node);
void	*gb_malloc(size_t size, int type);
// -------------------------------

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_p_cmd
{
	int				pipe_line;
	char			*line;
	char			**cmd;
	char			**redir;
	struct s_p_cmd	*next;
}	t_p_cmd;

typedef struct s_cmd
{
	int				pipe_line;
	char			**args;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_utils
{
	char	c;
	int		fd;
	int		i;
	int		j;
	int		k;
	char	*new_line;
	int		sq;
	int		dq;
	int		*fds_tab;
	char	*f_name;
	int		status;
	int		len;
	int		flag;
}	t_utils;

// lib_utils
void	*ft_malloc(size_t size, int free);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(char *s1, char *s2, size_t size);
void	ft_putstr_fd(char *str, int fd);
void	ft_error(char *str);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_free(char **tab);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strtrim_(char *str);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
int		size_array(char **array);

// lib_utils_2
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_strcpy(char *dst, char *src);
void	ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		all_space(char *line);
int		ft_check_syntax(char *line);
int		ft_check_direction(char *line);
int		ft_isspace(char c);
int		is_caracter(char *str, char c);

// parsing_part

void	ft_parsing(char *line, t_p_cmd **cp_list, t_env *env_list);
char	**ft_split_cmd(char *line, char c, int s_q, int d_q);
int		cnt_split(char *line, char c, char t, int in_word);
int		is_expandable(char *line, int i, int *dq);
char	*ft_get_name(char *str, int i);
int		c_ex(char *str);
int		not_expandable(char c);
int		ft_to_ex(char c);
int		new_len(char *line, t_env *env);
void	*allocat_zero(size_t size);
int		ft_cnt_red(char *line, char c);
void	join_exit(char *new_line, int pipe_line, int *j, int *i);
void	join_val(t_env *env, char *line, char *new_line, int *j);
void	get_line(char *line, t_p_cmd *cp_list, t_env *env_list);
char	*get_redir(char *line, int i);
int		to_break(char l);
void	in_qote(int *sq, int *dq, char c);
char	**get_rd(char *line, int dq, int sq);
t_p_cmd	*ft_new_cp(char *cmd, int i, t_env *env_list);
void	cp_add_back(t_p_cmd **cp_list, t_p_cmd *new_cmd);
char	*expd_line(char *line, t_env *env, int pipe_line);
int		to_expand(char *line);
void	ft_merge(t_cmd **cmd_list, t_p_cmd *cp_list, t_env *env_list);
t_cmd	*ft_new_cmd(t_p_cmd *cp_cmd, t_env *env_list);
void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
char	*rm_qot(char *str, int s_q, int d_q);
void	close_tab(int *fd_tab, int size, int in, int out);
void	open_red(t_p_cmd *cmd, int *fd_in, int *fd_out, t_env *env);
char	*get_f_name(char *f_name, t_env *env, int pipe_line);
char	*expd_rd(char *f_name, t_env *env, int pipe_line);
int		err_get_name(t_utils **u, int *fd_in, int *fd_out);
char	*get_r_name(char *redir, t_env *env);
void	open_out(t_utils **u, char *red, int *fd_out);
void	open_in(t_utils **u, char *redir, int *fd_in);
void	unlinker(char **redir, int i, t_env *env);
int		exit_status(int status);
void	ft_handle_signals(void);
int		ft_maxsize(t_env *env_list, int flag);
void	herdoc_hundeler(t_p_cmd **cmd, t_env *env, int *sg);
char	*gnrt_name(void);
int		del_quote(int *sq, int *dq, char r);
int		to_herdoc(char *redir);
t_utils	*init_herd_uti(void);
void	unlik_herdoc(char **redir, int sig_flag);
void	ft_sig_herdoc(int sig);
int		cp_arr(char **in_redir);
int		will_expd(char *del);
char	*expended_buffer(char *buffer, t_env *env, int pipe_line);
// env_utils_1.c
char	**empty_env(void);
void	ft_change_env(t_env *env_list, char *name, char *value);
char	*ft_env_search(t_env *env_list, char *name);
t_env	*ft_env_new_(char *key, char *value);
t_env	*ft_env_new(char *env);
t_env	*ft_lstlast_env(t_env *env);
void	ft_env_add_back(t_env **env_list, t_env *new);
void	ft_env_list(t_env **env_list, char **env, int flag);
t_env	*find_env(t_env *env, char *name);
char	**ft_get_envp(t_env *env_list);
int		count_env(t_env *env);
char	**sort_env(t_env *env, int n);
void	ft_lst_clear_env(t_env **env);

//execution
void	ft_execut_cmd(t_cmd *cmd_list, t_env **env_list, int fd_in, int fd_out);
void	ft_execut(t_cmd *cmd_list, t_env *env_list);
char	*find_path_env(char *cmd, char *envp[]);
int		fork1(void);
void	ft_execution_error(char *str);
int		process_child(t_cmd *cmd_list, t_env **env_list, int fd[], int *flag);
int		process_child_end(t_cmd *cmd_list, t_env **env_list, int *flag);
void	pid_waiting(int flag);
void	wait_status(int pid, int flag);
char	*check_path(char **path_s, char *cmd);

//builtins
int		is_builtin(t_cmd *cmd_list);
int		ft_builtin(t_cmd *cmd_list, t_env **env_list);
int		ft_export_error(char *name);
int		max_index(t_cmd *cmd);
void	print_list_declare(t_env **env);
char	*check_name_env(char *name);
int		check_empty_value(char *var);
int		ft_echo(t_cmd *cmd_list);
int		ft_cd(t_cmd *cmd_list, t_env *env_list, char *old_pwd, char *path);
int		ft_pwd(t_env *env);
int		ft_export(t_cmd *cmd, t_env **env);
void	update_var(t_env **env, char *name, char *value, int flag);
int		ft_env(t_cmd *cmd, t_env *env);
int		ft_exit(t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_env **env);
void	shell_lvl(t_env *env);
int		is_ne_one(char *str);

//test
int		ft_lstsize(t_cmd *lst);
t_cmd	*ft_lstlast(t_cmd *lst);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew_cmd(char *cmd);
void	ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new);
void	close_fd(int fd_in, int fd_out);

//env_utils_4.c
char	*ft_strdup_(const char *s);
char	*ft_substr_(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_(char *s1, char *s2);
#endif