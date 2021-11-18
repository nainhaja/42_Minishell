/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:18:45 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 21:18:46 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_lastred(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == '>')
			cpt = i;
		i++;
	}
	return (cpt);
}

int	search_used_node(char *beforeeq, char *a_eq, t_list *g_shell)
{
	t_node	*tempp;

	tempp = g_shell->head;
	while (tempp->next != NULL)
	{
		if (ft_strcmp(tempp->next->beforeeq, beforeeq) == 0 && a_eq != 0)
		{
			free(tempp->next->aftereq);
			tempp->next->aftereq = ft_strdup(a_eq);
			return (1);
		}
		else if (ft_strcmp(tempp->next->beforeeq, beforeeq) == 0 && a_eq == 0)
			return (1);
		tempp = tempp->next;
	}
	return (0);
}
