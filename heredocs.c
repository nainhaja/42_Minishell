/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:14:41 by nainhaja          #+#    #+#             */
/*   Updated: 2021/11/07 14:14:42 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	opnening_files(void)
{
	int		cpt;
	char	*str;
	char	*s;

	cpt = 0;
	while (cpt < g_shell->hd_nbr)
	{
		s = ft_itoa(cpt);
		str = ft_strjoin("/tmp/file", s);
		g_shell->fds[cpt] = open(str,
				O_TRUNC | O_WRONLY | O_CREAT, 0777);
		cpt++;
		free(s);
		free(str);
	}
}

void	heredoc_handler(int sig_val)
{
	g_shell->g_signal = 1;
	if (g_shell->g_signal_sec)
	{
		g_shell->g_exit_code = 130;
		g_shell->g_signal_sec = 2;
		exit(0);
	}
	if (sig_val == 32)
		printf("");
}

void	treat_heredc(int cpt, char *str, char *s)
{
	signal(SIGINT, heredoc_handler);
	while (cpt < g_shell->hd_nbr)
	{
		str = remove_quotes(g_shell->heredoc[cpt]);
		while (1)
		{
			s = readline("> ");
			if (s == NULL)
				exit(0);
			if (ft_strcmp(s, str) == 0)
			{
				free(s);
				break ;
			}
			ft_putstr_fd(s, g_shell->fds[cpt]);
			ft_putstr_fd("\n", g_shell->fds[cpt]);
			free(s);
		}
		free(str);
		close(g_shell->fds[cpt]);
		cpt++;
	}
	exit(0);
}

void	check_heredc(int cpt, char *s, char *str, int id)
{
	g_shell->fds = malloc(sizeof(int) * g_shell->hd_nbr);
	opnening_files();
	if (g_shell->hd_nbr)
	{
		g_shell->g_signal_sec = 1;
		id = fork();
		if (id == 0)
			treat_heredc(cpt, str, s);
		else if (id > 0)
			wait(NULL);
	}
}

int	heredoc_number(int i, int flag)
{
	int	cpt;

	cpt = 0;
	while (g_shell->buffer[i])
	{
		if (is_quote(g_shell->buffer[i]) && flag == 0)
			flag = 1;
		else if (is_quote(g_shell->buffer[i]) && flag == 1)
			flag = 0;
		else
		{
			if (g_shell->buffer[i] == '<'
				&& flag == 0 && g_shell->buffer[i + 1] == '<'
				&& g_shell->buffer[i + 1] != '\0')
			{
				cpt++;
				i++;
			}
		}
		i++;
	}
	return (cpt);
}
