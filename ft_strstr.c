/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 05:36:20 by nainhaja          #+#    #+#             */
/*   Updated: 2019/07/19 00:41:11 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp2(char *str, char *to_find)
{
	while (*str && *to_find)
	{
		if (*str != *to_find)
			return (0);
		str++;
		to_find++;
	}
	if (*to_find == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	j;

	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (*str)
	{
		if ((to_find[j] == *str) && (ft_strcmp2(str, to_find) == 1))
			return (str);
		str++;
	}
	return (0);
}
