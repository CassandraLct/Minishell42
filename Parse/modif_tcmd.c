/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_tcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:17:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/27 17:55:04 by clecat           ###   ########.fr       */
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
		if (cmd[i][0] == '\'' || cmd[i][0] == '"')
		{
			rm_cotesline(cmd[i]);
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

char	*changecotesline(char *line, char cotes)
{
	char	*s_line;
	char	*e_line;
	char	*tmp;
	int		start;
	int		end;
	int		i;
	int		j;
	int		w;

	i = 0;
	w = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i] && line[i] != cotes)
		i++;
	j = i + 1;
	while (line[i] && line[i] != ' ' && i != 0)
		i--;
	start = i;
	s_line = malloc(sizeof(char) * ((j - i) + 2));
	if (i != 0)
	{
		while (line[w] && w <= i)
		{
			s_line[w] = line[w];
			w++;
		}
		s_line[w] = '\0';
		printf("s_line = {%s}\n", s_line);
	}
	while (line[j] && line[j] != cotes)
		j++;
	while (line[j] && (line[j] != ' ' || line[j] == '\0'))
		j++;
	end = j;
	printf("ici\n");
	if (line[j] != '\0')
	{
		e_line = malloc(sizeof(char) * ((ft_strlen(line) - j) + 1));
		printf("apres_malloc\n");
		w = 0;
		printf("avant boucle: j = %d\n", j);
		while (line[j] != '\0')
		{
			
			e_line[w] = line[j];
			w++;
			j++;
		}
		printf("ici2\n");
		e_line[w] = '\0';
		printf("e_line = {%s}\n", e_line);
	}
	i = 0;
	while (line[start] && start <= end)
	{
		tmp[i] = line[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	printf("changes cotes line : tmp = %s\n", tmp);
	return (tmp);
}

char	*add_cotesout(char *line)
{
	char	*tmp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(line) + 3));
	tmp[j] = '"';
	j += 1;
	while (line[i])
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '"';
	tmp[j + 1] = '\0';
	return (tmp);
}

void	rm_cotes(char *line, char cotes)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		if (line[i] == cotes)
			i += 1;
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	printf("tmp = %s\n", tmp);
	free(line);
	line = add_cotesout(tmp);
	printf("after add_cote: line = %s\n", line);
	free(tmp);
}

void	check_line(char *line)
{
	char	*tmp;
	char	cotes;
	int		i;

	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if(line[i] == '\'' || line[i] == '"')
			break;
		i++;
	}
	if (line[i] == '\0')
		return ;
	cotes = line[i];
	tmp = changecotesline(line, cotes);
	printf("tmp = %s\n", line);
	rm_cotes(tmp, cotes);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
}

//recuperer ce qu'il y avant et apres l'espace
//gestion des cotes au milieu d'une commande
void	verif_cmdcotes(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	printf("line = %s\n", line);
	tmp = ft_strdup(line);
	check_line(tmp);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
}
