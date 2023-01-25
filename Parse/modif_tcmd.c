/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_tcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:17:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/25 12:32:11 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//supprime les cotes exterieurs
void	rm_cotesline(char *line)
{
	char	*tmp;
	char	cotes;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * ft_strlen(line));
	cotes = line[0];
	i = 1;
	j = 0;
	while (line[i] && line[i] != cotes && line[i + 1] != '\0')
	{
		tmp[j] = line[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(line);
	line = ft_strdup(tmp);
	printf("tmp = %s\n", tmp);
	free(tmp);
}

//modifie la ligne cmd ou sort
void	modif_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == NULL)
		return ;
	while (cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		if (cmd[i][0] == '\'' || cmd[i][0] == '"')
			rm_cotesline(cmd[i]);
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
