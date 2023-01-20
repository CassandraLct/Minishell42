/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:22:20 by clecat            #+#    #+#             */
/*   Updated: 2023/01/20 16:55:36 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// // a remettre dans le makefile apres 	#Parse/dollar_var.c Parse/utils_dollar.c

// //recupere le nom de la variable (forcement un dollar)
// char	*recup_dollarvar(char *line)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
// 	while (line[i] && line[i] != '$')
// 		i++;
// 	i += 1;
// 	while (line[i] != '$' && line[i] != ' ' && line[i] != '\0')
// 		tmp[j++] = line[i++];
// 	tmp[j] = '\0';
// 	return (tmp);
// }

// char	*rm_dollarvar(char *tmp, char *str)
// {
// 	char	*start;
// 	char	*end;
// 	int		i;

// 	i = 0;
// 	start = recup_startline(tmp);
// 	while (tmp[i] && tmp[i] != '$')
// 		i++;
// 	while (tmp[i] != ' ' && tmp[i] != '\0')
// 		i++;
// 	if (i == ft_strlen(tmp))
// 	{
// 		if(start == NULL)
// 		{
// 			printf("start = %s, str = %s, line = %s\n", start, str, tmp);
// 			tmp = NULL;
// 			return (tmp);
// 		}
// 		else
// 		{
// 			free(tmp);
// 			tmp = ft_strdup(start);
// 			free(start);
// 			return (tmp);
// 		}
// 	}
// 	else
// 	{
// 		if(start == NULL)
// 		{
// 			end = recup_endline(i, tmp);
// 			free(tmp);
// 			tmp = ft_strdup(end);
// 			free(end);
// 			return (tmp);
// 		}
// 		else
// 		{
// 			end = recup_endline(i, tmp);
// 			free(tmp);
// 			tmp = ft_strjoin(start, end);
// 			free(start);
// 			free(end);
// 			return (tmp);
// 		}
// 	}
// 	return (tmp);
// }

// //recupere la valeur de la variable
// char	*recup_valvar(char *str)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = malloc(sizeof(char) * ft_strlen(str));
// 	while (str[i] != '=')
// 		i++;
// 	i += 1;
// 	while (str[i])
// 	{
// 		tmp[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	tmp[j] = '\0';
// 	return (tmp);
// }

// //tmp=line, 
// char	*change_linevar(char *tmp, char *val_var)
// {
// 	char	*new_line;
// 	char	*start;
// 	char	*end;
// 	int		i;

// 	i = 0;
// 	start = recup_startline(tmp);
// 	while (tmp[i] && tmp[i] != '$')
// 		i++;
// 	i += 1;
// 	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\0')
// 		i++;
// 	if (tmp[i] == '\0')
// 	{
// 		printf("dans le if\n");
// 		if(start == NULL)
// 		{
// 			printf("dans le if if\n");
// 			new_line = ft_strdup(val_var);
// 			return (new_line);
// 		}
// 		else
// 		{
// 			printf("dans le else else\n");
// 			free(tmp);
// 			tmp = ft_strjoin(start, val_var);
// 			free(start);
// 			return (tmp);
// 		}
// 	}
// 	else
// 	{
// 		printf("dans le else\n");
// 		if(start == NULL)
// 		{
// 			end = recup_endline(i, tmp);
// 			free(tmp);
// 			tmp = ft_strjoin(val_var, end);
// 			return (tmp);
// 		}
// 		else
// 		{
// 			new_line = ft_strjoin(start, val_var);
// 			end = recup_endline(i, tmp);
// 			free(tmp);
// 			tmp = ft_strjoin(new_line, end);
// 			free(new_line);
// 			free(end);
// 			free(start);
// 			return(tmp);
// 		}
// 	}
// 	return (tmp);
// }

// char	*dollar_reterr(char *tmp)
// {
// 	char	*val_var;
// 	char	*start;
// 	char	*end;
// 	int		i;

// 	i = 0;
// 	printf("dans dollar ret_err\n");
// 	start = recup_startline(tmp);
// 	printf("ici, start = %s\n", start);
// 	if(start != NULL)
// 		val_var = ft_strjoin(start, ft_itoa(g_mini.ret_err));
// 	else
// 		val_var = ft_itoa(g_mini.ret_err);
// 	printf("ici 2, val_var = %s\n", val_var);
// 	while(tmp[i] && tmp[i] != '$')
// 		i++;
// 	while (tmp[i] && tmp[i] != '$' && tmp[i] != ' ' &&tmp[i] != '\0')
// 		i++;
// 	printf("ici 3, i = %d, tmp = %s\n", i, tmp);
// 	if (tmp[i] == '\0')
// 	{
// 		printf("dans le if strlen\n");
// 		free(tmp);
// 		tmp = ft_strdup(val_var);
// 		free(val_var);
// 		return (tmp);
// 	}
// 	else
// 	{
// 		printf("dans le else\n");
// 		end = recup_endline(i, tmp);
// 		printf("end = %s\n", end);
// 		if(end == NULL)
// 		{
// 			free(tmp);
// 			tmp = ft_strdup(val_var);
// 		}
// 		else
// 		{
// 			free(tmp);
// 			tmp = ft_strjoin(val_var, end);
// 			free(val_var);
// 			free(end);
// 			return (tmp);
// 		}
// 	}
// 	return (tmp);
// }

// //tmp = nom var+= puis a line
// char	*ft_dollar(char *str, t_min *mini, char *line)
// {
// 	char	*tmp;
// 	char	*val_var;
// 	char	*tmp1;
// 	int		i;

// 	i = 0;
// 	if(str[i] != '?')
// 	{
// 		tmp1 = ft_strdup(str);
// 		free(str);
// 		val_var = ft_strjoin(tmp1, "=");
// 	}
// 	if (str[i] == '?')
// 	{
// 		tmp = ft_strdup(line);
// 		free(line);
// 		line = dollar_reterr(tmp);
// 		free(str);
// 		val_var = ft_strjoin(line, "=");
// 		free(tmp);
// 	}
// 	while (mini->c_env[i])
// 	{
// 		if (ft_strncmp(mini->c_env[i], val_var, ft_strlen(val_var)) == 0)
// 			break ;
// 		i++;
// 	}
// 	if (i == tablen(mini->c_env))
// 	{
// 		tmp = ft_strdup(line);
// 		line = rm_dollarvar(tmp, str);
// 		free(tmp);
// 		if (!line)
// 			return (NULL);
// 		else
// 			return(line);
// 	}
// 	else
// 	{
// 		free(val_var);
// 		tmp = ft_strdup(line);
// 		val_var = recup_valvar(mini->c_env[i]);
// 		free(line);
// 		line = change_linevar(tmp, val_var);
// 		free(tmp);
// 		free(val_var);
// 		return (line);
// 	}
// }

// //tmp = nom variable
// char	*redir_gestdollar(int nb_dollar, t_min *mini)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		k;

// 	tmp = NULL;
// 	k = 0;
// 	line = ft_strdup(mini->line);
// 	if(nb_dollar == 1)
// 	{
// 		tmp = recup_dollarvar(line);
// 		free(mini->line);
// 		mini->line = ft_dollar(tmp, mini, line);
// 		printf("line3 = %s\n", g_mini.line);
// 		return (mini->line);
// 	}
// 	else
// 	{
// 		while(k != nb_dollar)
// 		{
// 			tmp = recup_dollarvar(mini->line);
// 			printf("tmp = %s\n", tmp);
// 			free(mini->line);
// 			mini->line = ft_dollar(tmp, mini, line);
// 			free(tmp);
// 			k++;
// 		}
// 		return (mini->line);
// 	}
// }

// //supprime le double dollar
// char	*rm_d_dollar(char *tmp)
// {
// 	char	*new_line;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new_line = malloc(sizeof(char) * ft_strlen(tmp));
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '$' && tmp[i + 1] == '$')
// 			i += 2;
// 		new_line[j] = tmp[i];
// 		j++;
// 		i++;
// 	}
// 	new_line[j] = '\0';
// 	return (new_line);
// }
