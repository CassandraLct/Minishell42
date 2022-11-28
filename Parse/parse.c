/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:24 by clecat            #+#    #+#             */
/*   Updated: 2022/11/28 11:24:33 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//3 fonctions
//malloc la taille du tableau
char	**init_exp(char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = init_cpy(tab, tmp);
	tmp[i] = NULL;
	return (tmp);
}

char	**init_cpy(char **str, char **dest)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	return (dest);
}

//effectue une copie de char**
char	**ft_cpytab(char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = init_cpy(tab, tmp);
	while (tab[i])
	{
		tmp[i] = ft_strdup(tab[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
