/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:15:29 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/22 22:42:06 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*get_before_eq(char *str, int *i)
{
	int		start;
	char	*before_eq;
	char	*s;

	start = 0;
	*i = 0;
	while (str[*i] != '=' && str[*i] != '\0')
		*i = *i + 1;
	s = ft_substr(str, start, *i - start);
	before_eq = s;
	return (before_eq);
}

void	clear_leaks(char *ptr, int start, int i)
{
	char	*ss;
	char	*s;

	ss = g_shell->buffer;
	s = ft_substr(g_shell->buffer, start, i - start);
	if (start != 0)
		g_shell->buffer = ft_strjoin(ptr, s);
	if (ss != g_shell->buffer)
		free(ss);
	free(s);
}
