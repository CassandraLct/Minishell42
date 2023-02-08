/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:57:22 by clecat            #+#    #+#             */
/*   Updated: 2023/02/08 14:23:33 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*recup_rcmd(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
		i++;
	while (i != 0 && line[i] != '/')
		i--;
	tmp = malloc(sizeof(char) * ((ft_strlen(line) - i) + 1));
	i += 1;
	while (line[i])
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

//cas /bin/echo etc + verification si l'arg avant est une cmd existante
char	*check_cmd(char *line)
{
	char	*real_cmd;
	int		nb_slash;
	int		i;

	i = 0;
	nb_slash = 0;
	real_cmd = NULL;
	while (line[i])
	{
		if(line[i] == '/')
			nb_slash += 1;
		i++;
	}
	if(nb_slash < 2)
		return (line);
	else if (nb_slash >= 2)
	{
		i = 0;
		if (line[0] == '/')
		{
			if (access(line, R_OK) == 0)
			{
				real_cmd = recup_rcmd(line);
				free(line);
				line = ft_strdup(real_cmd);
				free(real_cmd);
			}
		}
	}
	return (line);
}