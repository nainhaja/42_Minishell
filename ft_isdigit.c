/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:21:10 by nainhaja          #+#    #+#             */
/*   Updated: 2019/10/16 16:24:54 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	else
		return (0);
}

void	pwd(int flag)
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	if (flag == 1)
		exit(0);
}

void	exit_cases(char **str, int i)
{
	if ((int)ft_strlen(str[0]) != i)
	{
		printf("Minishell: exit: %s: numeric argument required\n", str[0]);
		g_shell->g_exit_code = 255;
		exit(g_shell->g_exit_code);
	}
	else
		exit(ft_atoi(g_shell->rest));
}

void	treating_exit(void)
{
	char	**str;
	int		i;

	str = ft_split_spaces(g_shell->buffer, ' ');
	printf("exit\n");
	if (str[0] == NULL)
		exit(g_shell->g_exit_code);
	else if (str[1] == NULL)
	{	
		if (str[0][0] == '-')
			i = 1;
		else
			i = 0;
		while (ft_isdigit(str[0][i]))
			i++;
		exit_cases(str, i);
	}
	else
	{
		printf("Minishell: exit: too many arguments\n");
		g_shell->g_exit_code = 1;
	}
}

char	*send_it(char *s, char *ptr, int i, int start)
{
	char	*str;

	s = ptr;
	str = ft_substr(g_shell->buffer, start, i - start);
	ptr = ft_strjoin(ptr, str);
	free(s);
	free(str);
	return (ptr);
}
