/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:43:29 by clecat            #+#    #+#             */
/*   Updated: 2023/01/18 16:27:23 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//5 fonctions
//recupere la valeur de la variable
char	*recup_valvar(char *str)
{
	char	*tmp;
	int		i;
	int		j;

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

//supprime la variable non existante de la line +25lignes
void	rm_dollarvar(void)
{
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = recup_startline(g_mini.line);
	while (g_mini.line[i] && g_mini.line[i] != '$')
		i++;
	while (g_mini.line[i] != ' ' && g_mini.line[i] != '\0')
		i++;
	if (i == ft_strlen(g_mini.line))
	{
		free(g_mini.line);
		g_mini.line = ft_strdup(start);
		free(start);
	}
	else
	{
		end = recup_endline(i, g_mini.line);
		free(g_mini.line);
		g_mini.line = ft_strjoin(start, end);
		free(start);
		free(end);
	}
}

//change valeur de la var dans la line +25 lignes
void	change_linevar(char *str)
{
	char	*tmp;
	char	*start;
	char	*end;
	int		i;

	start = recup_startline(g_mini.line);
	i = ft_strlen(start) + 1;
	tmp = ft_strjoin(start, str);
	free(start);
	while (g_mini.line[i] != ' ' && g_mini.line[i] != '\0')
		i++;
	if (i == ft_strlen(g_mini.line))
	{
		free(g_mini.line);
		g_mini.line = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		end = recup_endline(i, g_mini.line);
		free(g_mini.line);
		g_mini.line = ft_strjoin(tmp, end);
		free(tmp);
		free(end);
	}
}

void	dollar_reterr(char *line)
{
	char	*tmp;
	char	*start;
	char	*end;
	int		i;

	start = recup_startline(line);
	i = ft_strlen(start) + 1;
	tmp = ft_strjoin(start, ft_itoa(g_mini.ret_err));
	free(start);
	while (line[i] && line[i] != ' ' && line[i] != '\0')
		i++;
	if (i == ft_strlen(line))
	{
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		end = recup_endline(i, g_mini.line);
		free(line);
		line = ft_strjoin(tmp, end);
		free(tmp);
		free(end);
	}
}

//gestion dollar 
void	ft_dollar(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (str[i] == '?')
		dollar_reterr(g_mini.line);
	tmp = ft_strjoin(str, "=");
	while (g_mini.c_env[i])
	{
		if (ft_strncmp(g_mini.c_env[i], tmp, ft_strlen(tmp)) == 0)
			break ;
		i++;
	}
	free(tmp);
	if (i == tablen(g_mini.c_env))
		rm_dollarvar();
	else
	{
		tmp = recup_valvar(g_mini.c_env[i]);
		change_linevar(tmp);
		free(tmp);
	}
}
