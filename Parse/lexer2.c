/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:03:48 by clecat            #+#    #+#             */
/*   Updated: 2023/01/10 16:14:50 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// line = echo -n | ls
//faire le verif cotes

char	**split_on_cmd(t_min mini)
{
	char	**tab_proc;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		if (mini.line == "|")
			j += 1;
		i++;
	}
	tab_proc = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (mini.line[i] != "|")
	{
		tab_proc = mini.line[i];
		i++;
	}
}