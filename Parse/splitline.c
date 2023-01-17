/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/13 16:15:49 by clecat           ###   ########.fr       */
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

char	**spliter(t_min mini)
{
	char	**result;
	int		i;
	int		cote;
	int		instrucnb;
	char	*temp;
	int		j;
	int		k;

	result = NULL;
	if (iscotevalid(mini.line) == 0)
	{
		printf("command not valid\n");
		return (NULL);
	}
	else
		printf("command is valid\n");
	i = count_instruct(mini.line);
	result = malloc((i + 1) * sizeof(*result));
	if (!result)
		return (NULL);
	temp = malloc((ft_strlen(mini.line) + 1) * sizeof(*temp));
	ft_bzero((void *)temp, ft_strlen(mini.line) + 1);
	ft_putstr_fd(temp, 2);
	instrucnb = 0;
	j = 0; // index du char dans mini.line
	k = 0; // index du char dans l instruction
	cote = 0; // indique si on est dans une cote simple ou double
	while (mini.line[j])
	{
		if (mini.line[j] == '|' && mini.line[j + 1] != '|' && cote == 0)
		{
			result[instrucnb] = malloc((ft_strlen(temp) + 1) * sizeof (*result[instrucnb]));
			result[instrucnb] = ft_strdup(temp);
			ft_bzero(temp, ft_strlen(mini.line) + 1);
			instrucnb++;
			k = 0;
		}
		else
		{
			temp[k] = mini.line[j];
			if (mini.line[j] == '\'' || mini.line[j] == '"')
				cote = (cote + 1) % 2;
			k++;
		}
		j++;
	}
	result[instrucnb] = malloc((ft_strlen(temp) + 1) * sizeof (*result[instrucnb]));
	result[instrucnb] = ft_strdup(temp);
	result[instrucnb + 1] = NULL;
	free(temp);
	return (result);
}
