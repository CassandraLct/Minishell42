/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:23:50 by clecat            #+#    #+#             */
/*   Updated: 2023/01/16 10:56:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//verifier pipe sans arg affiche le message d'erreur que lors du exit
// int	verif_pipe(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
// 		i++;
// 	if (line[i] == '|' && (line[i + 1] == '\0' || line[i + 1] == 32
// 		|| (line[i + 1] >= 9 && line[i + 1] <= 13)))
// 		return (1);
// 	return(0);
// }

int	verif_quotes(char *line)
{
	char	c;
	int		i;
	int		count;

	i = 0;
	while (line[i] == 32 || line[i] >= 9 && line[i] <= 13)
		i++;
}

//premier split sur les pipes 
//pipe en fin de ligne et cotes penser a enlever les espaces
char	**split_onpipe(t_min mini)
{
	if (verif_quote(mini.line) == 0)
		printf("cotes presente\n");
	else
		mini.tab = ft_split(mini.line, '|');
	return (mini.tab);
}
