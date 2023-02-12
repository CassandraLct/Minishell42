/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 15:15:50 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//5 fonctions
//remove all the multiple space to keep only one
char	*remove_double_char(char *line, char c, int remove_both_char)
{
	char	*resu;
	int		i;
	int		j;

	i = ft_strlen(line) + 1;
	resu = ft_test(ft_calloc(i, sizeof(*resu)), NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!(line[i] == c && line[i + 1] == c))
		{
			resu[j] = line[i];
			j++;
		}
		else if (remove_both_char)
			i++;
		i++;
	}
	return (resu);
}
