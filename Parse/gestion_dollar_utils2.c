/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:14:50 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 17:23:17 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//copy name var without ?
char	*copy_tmp(char *line, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (line[i])
	{
		j++;
		i++;
	}
	tmp = malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (line[i] && line[i] != '?')
		i++;
	i += 1;
	while (line[i])
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
