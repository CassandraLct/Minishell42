/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/18 23:40:56 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 0 if the '(39) or the "(34) are mixed or not by even number
int	iscotevalid(char *line)
{
	int	i;
	int	simplecote;
	int	doublecote;

	i = 0;
	simplecote = 0;
	doublecote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && doublecote == 0)
			simplecote = (simplecote + 1) % 2;
		else if (line[i] == '"' && simplecote == 0)
			doublecote = (doublecote + 1) % 2;
		i++;
	}
	if (simplecote == 1 || doublecote == 1)
		return (0);
	return (1);
}

// count how many instructions are between the real pipes
int	count_instruct(char *line)
{
	int	i;
	int	nbinst;

	i = 0;
	nbinst = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
		}
		else if (line[i] == '|' && line[i + 1] != '|')
			nbinst++;
		i++;
	}
	return (nbinst + 1);
}

// test if a the variable is different from error
// used to test if the malloc are ok
void	*ft_test(void *var, void *error)
{
	if (var == error)
	{
		perror(NULL);
		exit(1);
	}
	return (var);
}

// return one if the char j is a real pipe
// a real pipe is a pipe that is not inside a cote
int	is_single_pipe(int j)
{
	int	i;
	int	cote;

	i = 0;
	cote = 0;
	if (g_mini.line[0] == '|' && g_mini.line[0] != '|')
	{
		printf("minishell: parse error near `|'\n");
		exit (1);
	}
	while (i < j)
	{
		if (g_mini.line[i] == '\'' || g_mini.line[i] == '"')
				cote = (cote + 1) % 2;
		i++;
	}
	if (j == 0)
		return (0);
	if (cote != 1 && g_mini.line[j] == '|' && g_mini.line[j + 1] != '|'
		&& g_mini.line[j - 1] != '|')
		return (1);
	return (0);
}

// main loop of spliter 
char	**spliter_loop(char **resu, char *temp)
{
	int		inb;
	int		j;
	int		k;

	inb = 0;
	j = 0;
	k = 0;
	while (g_mini.line[j])
	{
		if (is_single_pipe(j) == 1)
		{
			resu[inb++] = ft_strdup(temp);
			k = 0;
		}
		else
		{
			temp[k++] = g_mini.line[j];
			temp[k] = '\0';
		}
		j++;
	}
	resu[inb] = ft_strdup(temp);
	resu[inb + 1] = NULL;
//	free(temp);
	return (resu);
}

// cut the line received from readline, the separator are real pipes 
char	**spliter(void)
{
	char	**resu;
	int		i;
	char	*temp;

	resu = NULL;
	if (iscotevalid(g_mini.line) == 0)
	{
		printf("minishell: cote not closed\n");
		return (NULL);
	}
	i = count_instruct(g_mini.line);
	resu = ft_test(ft_calloc(i + 1, sizeof(*resu)), NULL);
	temp = ft_test(ft_calloc(ft_strlen(g_mini.line) + 1, sizeof(*temp)), NULL);
	resu = spliter_loop(resu, temp);
	free(temp);
	return (resu);
}

// cut the line received from readline, the separator are real pipes 
char	**spliter_old(void)
{
	char	**resu;
	int		i;
	int		cote;
	int		inb;
	char	*temp;
	int		j;
	int		k;

	resu = NULL;
	if (iscotevalid(g_mini.line) == 0)
	{
		printf("minishell: cote not closed\n");
		return (NULL);
	}
	i = count_instruct(g_mini.line);
	resu = ft_test(ft_calloc(i + 1, sizeof(*resu)), NULL);
	temp = ft_test(ft_calloc(ft_strlen(g_mini.line) + 1, sizeof(*temp)), NULL);
	inb = 0;
	j = 0;
	k = 0;
	cote = 0;
	while (g_mini.line[j])
	{
		if (g_mini.line[j] == '|' && g_mini.line[j + 1] != '|' && cote == 0)
		{
			resu[inb] = ft_strdup(temp);
			inb++;
			k = 0;
		}
		else
		{
			temp[k] = g_mini.line[j];
			if (g_mini.line[j] == '\'' || g_mini.line[j] == '"')
				cote = (cote + 1) % 2;
			k++;
			temp[k] = '\0';
		}
		j++;
	}
	resu[inb] = malloc((ft_strlen(temp) + 1) * sizeof (*resu[inb]));
	resu[inb] = ft_strdup(temp);
	resu[inb + 1] = NULL;
	free(temp);
	return (resu);
}
