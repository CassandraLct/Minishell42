/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_tcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:17:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/11 17:25:18 by rdi-marz         ###   ########.fr       */
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
	return (tmp);
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
		if (ft_strlen(cmd[i]) > 0 && (cmd[i][0] == '\'' || cmd[i][0] == '"'))
		{
			cmd[i][ft_strlen(cmd[i]) - 1] = '\0';
			tmp = ft_strdup(&(cmd[i][1]));
			free(cmd[i]);
			cmd[i] = tmp;
		}
		i++;
	}
	tmp = cmd[0];
	cmd[0] = check_cmd(tmp);
	free(tmp);
}

//modifie la lignes stdin ou sort
void	modif_stdin(char **stdin)
{
	char	*tmp;
	int		i;

	i = 0;
	if (stdin[0] == NULL)
		return ;
	while (stdin[i])
	{
		if (stdin[i][0] == '\'' || stdin[i][0] == '"')
		{
			tmp = ft_strdup(stdin[i]);
			free(stdin[i]);
			stdin[i] = rm_cotesline(tmp);
		}
		i++;
	}
}

//modifie la ligne stdout ou sort
void	modif_stdout(char **stdout)
{
	char	*tmp;
	int		i;

	i = 0;
	if (stdout[0] == NULL)
		return ;
	while (stdout[i])
	{
		if (stdout[i][0] == '\'' || stdout[i][0] == '"')
		{
			tmp = ft_strdup(stdout[i]);
			free(stdout[i]);
			stdout[i] = rm_cotesline(tmp);
		}
		i++;
	}
}
