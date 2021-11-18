/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:18:18 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:18:19 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *ptr, char *s)
{
	char	*test;

	test = ft_strjoin(ptr, " ");
	if (ft_check_restt() >= 1)
		test = ft_strjoin(test, s);
	return (test);
}

void	error_cmd(void)
{
	if (g_shell->f_cmd[0] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_shell->f_cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(g_shell->g_exit_code = 127);
	}
	else if (ft_strcmp(g_shell->f_cmd, ""))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_shell->f_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(g_shell->g_exit_code = 127);
	}
	else
		exit(g_shell->g_exit_code = 0);
}

void	execute(t_list *g_shell, char **argvv, char **envv)
{
	int		i;

	i = 0;
	if (g_shell->g_read == -1)
		exit(0);
	else
	{
		if (g_shell->f_cmd[0] == '/' || (g_shell->f_cmd[0] == '.'
				&& g_shell->f_cmd[1] == '/'))
			execve(g_shell->f_cmd, argvv, envv);
		else
		{
			if (g_shell->buffer[i] == '\'' && g_shell->buffer[i + 1] == '\'')
				error_cmd();
			while (g_shell->path[i])
			{
				execve(ft_strjoin(g_shell->path[i], g_shell->f_cmd),
					argvv, g_shell->env);
				i++;
			}
		}
	}
	error_cmd();
}

void	exec_cmd(t_list *g_shell)
{
	int		i;
	int		id;
	char	**argvv;

	g_shell->g_signal_sec = 1;
	id = fork();
	i = 0;
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		argvv = ft_split_spaces(ft_join(g_shell->f_cmd, g_shell->buffer), ' ');
		execute(g_shell, argvv, NULL);
		dup2(g_shell->stdio[1], 1);
	}
	else if (id > 0 && g_shell->pipx == 0)
	{
		wait_exec(1);
		wait(NULL);
		if (g_shell->g_signal && g_shell->hd_nbr)
			g_shell->g_exit_code = 1;
	}
	g_shell->g_signal_sec = 0;
	g_shell->g_signal = 0;
}

void	removee_spaces(t_list *g_shell)
{
	int		i;
	int		start;
	char	*res;
	int		flag;
	char	*ptr;

	res = ft_strdup("");
	i = 0;
	flag = 0;
	start = 0;
	ptr = res;
	while (g_shell->rest[i] != '\0')
	{
		while (g_shell->rest[i] == '\'' || g_shell->rest[i] == '"')
		{
			start = i;
			i = skip_quotes(i + 1, g_shell->rest[i], g_shell->rest);
			res = ft_strjoin(res, ft_substr(g_shell->rest, start, i - start));
		}
		i = skip_onlyspaces(i, g_shell, &res);
		i = get_only_char(g_shell->rest, i, &res);
	}
	g_shell->rest = remove_quotes(res);
	free(ptr);
}
