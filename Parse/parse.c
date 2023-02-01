/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:24 by clecat            #+#    #+#             */
/*   Updated: 2023/01/28 15:45:11 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
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

//free le double tableau
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

//renvoie vers les fonction correspondante
void	verif_struct_cmd(t_cmd **tab_scmd)
{
	int	i;

	i = 0;
	while (tab_scmd[0]->stdin[i])
		printf("stdin = {%s}\n", tab_scmd[0]->stdin[i++]);
	i = 0;
	while (tab_scmd[i])
	{
		modif_cmd(tab_scmd[i]->cmd);
		modif_stdin(tab_scmd[i]->stdin);
		modif_stdout(tab_scmd[i]->stdout);
		i++;
	}
}
