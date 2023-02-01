/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_tcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:17:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/01 10:52:40 by clecat           ###   ########.fr       */
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
	return(line);
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

char	*get_sline(char *line, char cotes)
{
	char	*s_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_line = NULL;
	while (line[i] && line[i] != cotes)
		i++;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<' && line[i] != '>')
		i--;
	j = ft_strlen(line) - i;
	if (i != 0)
	{
		s_line = malloc(sizeof(char) * ((ft_strlen(line) - j) + 1));
		j = 0;
		while (line[j] && j <= i)
		{
			s_line[j] = line[j];
			j++;
		}
		s_line[j] = '\0';
		return (s_line);
	}
	return (s_line);
}

char	*get_eline(char *line, char cotes)
{
	char	*e_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	e_line = NULL;
	while (line[i] && line[i] != cotes)
		i++;
	j = i + 1;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<' && line[i] != '>')
		i--;
	while (line[j] && line[j] != cotes)
		j++;
	while (line[j] && line[j] != ' ' && line[j] != '<' && line[j] != '>' && line[j] != '\0')
		j++;
	if (line[j] != '\0')
	{
		e_line = malloc(sizeof(char) * ((ft_strlen(line) - j) + 1));
		i = 0;
		while (line[j] != '\0')
		{
			
			e_line[i] = line[j];
			i++;
			j++;
		}
		e_line[i] = '\0';
		return (e_line);
	}
	return (e_line);
}

char	*changecotesline(char *line, char cotes)
{
	char	*tmp;
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i] && line[i] != cotes)
		i++;
	j = i + 1;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<' && line[i] != '>')
		i--;
	start = i;
	while (line[j] && line[j] != cotes)
		j++;
	while ((line[j] && line[j] != '\0' && line[j] != ' ' && line[j] != '<' && line[j] != '>'))
		j++;
	end = j;
	i = 0;
	if(line[start] == ' ' || line[start] == '<' || line[start] == '>')
		start += 1;
	while (line[start] && start != end)
	{
		tmp[i] = line[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*join_line(char *tmp, char *s_line, char *e_line)
{
	char	*new_line;
	char	*tmp2;

	tmp2 = NULL;
	new_line = NULL;
	if(s_line != NULL && e_line == NULL)
		new_line = ft_strjoin(s_line, tmp);
	else if(s_line != NULL && e_line != NULL)
	{
		tmp2 = ft_strjoin(s_line, tmp);
		new_line = ft_strjoin(tmp2, e_line);
		free(tmp2);
	}
	else if (s_line == NULL && e_line != NULL)
		new_line = ft_strjoin(tmp, e_line);
	else
		new_line = ft_strdup(tmp);
	return (new_line);
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

char	*rm_cotes(char *line, char cotes)
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
	free(line);
	line = add_cotesout(tmp);
	free(tmp);
	return (line);
}

char	*check_line(char *line)
{
	char	*tmp;
	char	*s_line;
	char	*e_line;
	char	cotes;
	int		i;

	i = 0;
	tmp = NULL;
	s_line = NULL;
	e_line = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (line);
	cotes = line[i];
	s_line = get_sline(line, cotes);;
	e_line = get_eline(line, cotes);
	tmp = changecotesline(line, cotes);
	tmp = rm_cotes(tmp, cotes);
	// free(line);
	line = join_line(tmp, s_line, e_line);
	free(tmp);
	if(s_line != NULL)
		free(s_line);
	if(e_line != NULL)
		free(e_line);
	return (line);
}

// int	verif_placecotes(char *line)
// {
// 	printf("verification placement des cotes, line = {%s}\n", line);
// 	return (0);
// }

//recuperer ce qu'il y avant et apres l'espace
//gestion des cotes au milieu d'une commande
char	*verif_cmdcotes(char *line)
{
	char	*tmp;
	char	*new_line;
//	int		i;

//	i = 0;
	new_line = NULL;
	tmp = ft_strdup(line);
	new_line = check_line(tmp);
	printf("new_line= %s\n", new_line);
	// free(line);
	return (new_line);
}
