/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:43:29 by clecat            #+#    #+#             */
/*   Updated: 2023/01/17 17:36:56 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//recupere la valeur de la variable
char	*recup_valvar(char *str)
{
	char	*tmp;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
		i++;
	i += 1;
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	rm_dollarvar(char *name)
{
	char	*start;
	char	*end;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	start = malloc(sizeof(char) * (ft_strlen(g_mini.line) - (ft_strlen(name) + 1)));
	while(g_mini.line[i] != '$')
	{
		start[i] = g_mini.line[i];
		i++;
	}
	start[i] = '\0';
	while(g_mini.line[i] != ' ' && g_mini.line[i] != '\0')
		i++;
	if(i == ft_strlen(g_mini.line))
	{
		free(g_mini.line);
		g_mini.line = ft_strdup(start);
	}
	else
	{
		end = malloc(sizeof(char) * (ft_strlen(g_mini.line) - (ft_strlen(name) + 1)));
		while(g_mini.line[i])
		{
			end[j] = g_mini.line[i];
			i++;
		}
		end[j] = '\0';
		free(g_mini.line);
		g_mini.line = ft_strjoin(start, end);
		free(start);
		free(end);
	}
}

void	change_linevar(char *str)
{
	char	*tmp;
	char	*start;
	char	*end;
	int		i;
	int		j;

	i = 0;
	j = 0;
	start = malloc(sizeof(char) * ft_strlen(g_mini.line));
	while (g_mini.line[i] != '$')
	{
		start[i] = g_mini.line[i];
		i++;
	}
	start[i] = '\0';
	tmp = ft_strjoin(start, str);
	free(start);
	while (g_mini.line[i] != ' '  && g_mini.line[i] != '\0')
		i++;
	if(i == ft_strlen(g_mini.line))
	{
		free(g_mini.line);
		g_mini.line = ft_strdup(tmp);
	}
	else
	{
		end = malloc(sizeof(char) * ft_strlen(g_mini.line));
		while (g_mini.line[i])
		{
			end[j] = g_mini.line[i];
			j++;
			i++;
		}
		end[j] = '\0';
		free(g_mini.line);
		g_mini.line = ft_strjoin(tmp, end);
		free(tmp);
		free(end);
	}
}

//gestion dollar //segfault
void	ft_dollar(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(str, "=");
	while(g_mini.c_env[i])
	{
		if(ft_strncmp(g_mini.c_env[i], tmp, ft_strlen(tmp)) == 0)
			break ;
		i++;
	}
	free(tmp);
	if (i == tablen(g_mini.c_env))
		rm_dollarvar(str);
	else
	{
		str = recup_valvar(g_mini.c_env[i]);
		change_linevar(str);
	}
}

/*
	si variable existante mais aucune commande 
	printf("minishell: (valeur variable): is a directory\n");
*/