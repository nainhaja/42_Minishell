/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:46:06 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 16:46:07 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_pipe(t_list *g_shell)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (g_shell->buffer[i])
	{
		if (g_shell->buffer[i] == '"' || g_shell->buffer[i] == '\'')
			i = skip_quotes_sec(i + 1, g_shell->buffer[i], g_shell->buffer);
		if (g_shell->buffer[i] == '|')
			pipe++;
		if (g_shell->buffer[i] != '\0')
			i++;
	}
	return (pipe);
}

t_list	*ft_split_pipe(t_list *g_shell, int p, int *reminder, int *i)
{
	while (g_shell->buffer[*i])
	{
		if (g_shell->buffer[*i] == '"' || g_shell->buffer[*i] == '\'')
			*i = skip_quotes_sec(*i + 1, g_shell->buffer[*i], g_shell->buffer);
		if (g_shell->buffer[*i] == '|')
		{
			g_shell->tab[p] = ft_substr(g_shell->buffer,
					*reminder, *i - *reminder);
			*i = *i + 1;
			*reminder = *i;
			break ;
		}
		*i = *i + 1;
	}
	return (g_shell);
}

void	ft_last_command(t_list *g_shell, int p, int *reminder)
{
	g_shell->tab[p] = ft_substr(g_shell->buffer, *reminder,
			ft_strlen(g_shell->buffer) - *reminder);
	g_shell->tab[++p] = NULL;
}

void	ft_initiate_pipe(t_list *g_shell)
{
	int		i;
	int		in;
	int		fd[2];

	i = 0;
	in = 0;
	while (g_shell->tab[i + 1] != NULL)
	{
		pipe(fd);
		ft_spawn_process(in, fd, g_shell, i);
		if (fd[1] > 2)
			close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		i++;
		g_shell->f_cmd = NULL;
		g_shell->rest = NULL;
	}
	ft_last_pipe(in, fd, g_shell, i);
	wait_exec(i);
}

void	split_cmds_pipes(int indice, int i, int reminder)
{
	int	pipe;

	g_shell->g_read = 0;
	g_shell->pipe_cpt = 0;
	check_heredoc(g_shell);
	expand_command(g_shell);
	pipe = ft_check_pipe(g_shell);
	g_shell->tab = malloc(sizeof(char *) * (pipe + 2));
	while (indice < pipe)
	{
		g_shell->pipx++;
		ft_split_pipe(g_shell, indice, &reminder, &i);
		indice++;
	}
	ft_last_command(g_shell, indice, &reminder);
	if (ft_error_pipe() || error_pipe(pipe))
		return ;
	ft_initiate_pipe(g_shell);
	free_tab();
	free(g_shell->buffer);
}
