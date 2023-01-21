/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:31:40 by clecat            #+#    #+#             */
/*   Updated: 2023/01/21 19:51:22 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//recupere le debut de la ligne
char	*recup_startline(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (i == 0)
		tmp = NULL;
	else
	{
		tmp = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (line[i] && line[i] != '$')
		{
			tmp[i] = line[i];
			i++;
		}
		tmp[i] = '\0';
	}
	return (tmp);
}

//recupere la fin de la ligne
char	*recup_endline(int i, char *line)
{
	char	*tmp;
	int		j;

	j = 0;
	if (i == 0)
		tmp = NULL;
	else
	{
		tmp = malloc(sizeof(char) * ((ft_strlen(line) - i) + 1));
		while (line[i])
		{
			tmp[j] = line[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
	}
	return (tmp);
}

// //recupere le nom de la variable (forcement un dollar)
// char	*recup_dollarvar(char *line)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
// 	while (line[i] && line[i] != '$')
// 		i++;
// 	i += 1;
// 	while (line[i] != '$' && line[i] != ' ' && line[i] != '\0')
// 		tmp[j++] = line[i++];
// 	tmp[j] = '\0';
// 	return (tmp);
// }

// //recupere la valeur de la variable
// char	*recup_valvar(char *str)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = malloc(sizeof(char) * ft_strlen(str));
// 	while (str[i] != '=')
// 		i++;
// 	i += 1;
// 	while (str[i])
// 	{
// 		tmp[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	tmp[j] = '\0';
// 	return (tmp);
// }
