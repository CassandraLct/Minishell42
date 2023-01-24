/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:05:30 by clecat            #+#    #+#             */
/*   Updated: 2023/01/24 19:46:04 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//supprime le dollar en dehors des cotes 
char	*rmd_bf_cotes(char *line, int savedollar)
{
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line));
	while (line[i])
	{
		if (i == savedollar)
			i += 1;
		tmp[x] = line[i];
		x++;
		i++;
	}
	tmp[x] = '\0';
	printf("tmp = %s\n", tmp);
	return (tmp);
}

//cas du dollar en dehors des cotes
void	d_outside_cotes(int i, char *line)
{
	int	savedollar;

	savedollar = i;
	while (line[i] && line[i] != '\'' && line[i] != '"')
		i++;
	if (line[i] == '\0')
		return ;
	else
		rm_dollarcotes(line, i, savedollar);
}
