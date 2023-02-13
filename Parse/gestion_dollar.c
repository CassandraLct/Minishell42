/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:51:02 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 11:28:49 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
//verifie la position du ?
void	verif_posreterr(char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((*line)[i] == '?' && (*line)[i + 1] != '\0')
	{
		i += 1;
		tmp = copy_tmp(*line, i);
		free(*line);
		*line = ft_strdup(tmp);
		free(tmp);
	}
}

//change le $?
char	*var_reterr(char *line)
{
	char	*name_var;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_itoa(g_mini.ret_err);
	tmp = recup_namevar(line);
	verif_posreterr(&tmp);//leaks
	if (strlen(tmp) > 1)
		name_var = ft_strjoin(tmp2, tmp);
	else
		name_var = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
	tmp = change_line(name_var, line);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

//change la val de la var existante
char	*var_true(char *line)
{
	char	*name_var;
	char	*tmp;

	name_var = recup_namevar(line);
	tmp = recup_valvar(name_var);
	name_var = ft_strdup(tmp);
	free(tmp);
	tmp = change_line(name_var, line);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

//supprime la var non-existante de la line
char	*var_false(char *line)
{
	char	*name_var;
	char	*tmp;

	if (verif_redirdollar(line) == 1)
	{
		name_var = recup_namevar(line);
		ft_print_error_msg3("minishell: $", name_var,
			": ambiguous redirect\n");
		free(name_var);
		g_mini.ret_err = 1;
		return (line);
	}
	else if (verif_redirdollar(line) == 2)
		return (line);
	else
	{
		name_var = malloc(sizeof(char) * 1);
		name_var[0] = '\0';
		tmp = change_line(name_var, line);
		free(line);
		line = ft_strdup(tmp);
		free(tmp);

	}
	return (line);
}

//redirection vers les fonctions de modifications +25lignes
char	*redir_line(char *line, int nb_dollar)
{
	char	*tmp_line;

	tmp_line = ft_strdup(line);
	while (nb_dollar != 0)
	{
		free(line);
		if (verif_dollarcase(tmp_line) == 1)
			line = var_reterr(tmp_line);
		else if (verif_dollarcase(tmp_line) == 2)
			line = var_true(tmp_line);
		else if (verif_dollarcase(tmp_line) == 3)
			line = var_false(tmp_line);
		else if (verif_dollarcase(tmp_line) == 4)
		{
			line = ft_strdup(tmp_line);
			free(tmp_line);
			return (line);
		}
		tmp_line = ft_strdup(line);
		nb_dollar--;
	}
	free(tmp_line);
	return (line);
}
