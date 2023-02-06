/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_tcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:17:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/06 16:50:48 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//supprime les cotes exterieurs
char	*rm_cotesline(char *line)
{
	char	*tmp;

	char	cotes;
	int		i;
	int		j;

	cotes = line[0];
	i = 1;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line));
	while (line[i] && line[i] != cotes && line[i + 1] != '\0')
	{
		tmp[j] = line[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

//modifie la ligne cmd ou sort
void	modif_cmd(char **cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (cmd[0] == NULL)
		return ;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'' || cmd[i][0] == '"')
		{
			tmp = ft_strdup(cmd[i]);
			free(cmd[i]);
			cmd[i] = rm_cotesline(tmp);
		}
		i++;
	}
}

//modifie la lignes stdin ou sort
void	modif_stdin(char **stdin)
{
	int	i;

	i = 0;
	if (stdin[0] == NULL)
		return ;
	while (stdin[i])
	{
		if (stdin[i][0] == '\'' || stdin[i][0] == '"')
			rm_cotesline(stdin[i]);
		i++;
	}
}

//modifie la ligne stdout ou sort
void	modif_stdout(char **stdout)
{
	int	i;

	i = 0;
	if (stdout[0] == NULL)
		return ;
	while (stdout[i])
	{
		if (stdout[i][0] == '\'' || stdout[i][0] == '"')
			rm_cotesline(stdout[i]);
		i++;
	}
}

//free str in check_line
void	free_seline(char *s_line, char *e_line)
{
	if (s_line != NULL)
		free(s_line);
	if (e_line != NULL)
		free(e_line);
}
