/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:12:25 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/16 21:21:17 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int str)
{
	if ((str >= 'A' && str <= 'Z') || (str >= 'a' && str <= 'z'))
		return (1);
	else
		return (0);
}

void	ft_check_empty(void)
{
	if (g_shell->buffer[0] == '\'' && g_shell->buffer[1] == '\'')
		printf("minishell: : coommand not found\n");
	else if (g_shell->buffer[0] == '"' && g_shell->buffer[1] == '"')
		printf("minishell: : coommand not found\n");
}

int	ft_error_pipe(void)
{
	int	i;

	i = 0;
	while (g_shell->buffer[i] == ' ')
		i++;
	if (g_shell->buffer[i] == '|' && g_shell->buffer[i + 1] == '|')
	{
		printf("Minishell: syntax error near unexpected token `||'\n");
		g_shell->g_exit_code = 258;
		return (1);
	}
	return (0);
}

int	error_pipe(int pipe)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < pipe)
	{
		if (g_shell->tab[i] == NULL || ft_strcmp(g_shell->tab[i], "") == 0)
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			g_shell->g_exit_code = 258;
			return (1);
		}
		i++;
		while (g_shell->tab[i][j] == ' ' && g_shell->tab[i][j])
			j++;
		if (j == (int)ft_strlen(g_shell->tab[i]))
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			g_shell->g_exit_code = 258;
			return (1);
		}	
	}
	return (0);
}
