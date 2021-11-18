/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 21:24:45 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/22 22:44:16 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int	implement(int i, char **ptr, int *start)
{
	if (g_shell->buffer[i] == '>' && g_shell->buffer[i + 1] == '>')
		i = double_redr(g_shell, ptr, start, i);
	if (g_shell->buffer[i] == '>' && g_shell->buffer[i + 1] != '>')
		i = single_redr(g_shell, ptr, start, i);
	if (i == -1)
		return (-1);
	return (i);
}

int	red_quotes(int i, int *flag)
{
	if (is_quote(g_shell->buffer[i]) && *flag == 0)
	{
		*flag = 1;
		return (1);
	}
	else if (is_quote(g_shell->buffer[i]) && *flag == 1)
	{
		*flag = 0;
		return (1);
	}
	return (0);
}

void	skip_it(int *i, char **res)
{
	char	*str;
	int		start;

	start = *i;
	*i = skip_quotes(*i + 1, g_shell->rest[*i], g_shell->rest);
	str = ft_substr(g_shell->rest, start, *i - start);
	*res = ft_strjoin(*res, str);
	free(str);
}
