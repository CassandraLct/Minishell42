/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:51:02 by clecat            #+#    #+#             */
/*   Updated: 2023/01/24 19:28:24 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//change le $?
char	*var_reterr(char *line)
{
	char	*name_var;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_itoa(g_mini.ret_err);
	name_var = ft_strdup(tmp2);
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

	name_var = malloc(sizeof(char) * 1);
	name_var[0] = '\0';
	tmp = change_line(name_var, line);
	printf("tmp = %s\n", tmp);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

//redirection vers les fonctions de modifications +25lignes
char	*redir_line(char *line, int nb_dollar)
{
	char	*tmp_line;

	tmp_line = ft_strdup(line);
	free(line);
	while (nb_dollar != 0)
	{
		if (verif_dollarcase(tmp_line) == 1)
			line = var_reterr(tmp_line);
		else if (verif_dollarcase(tmp_line) == 2)
			line = var_true(tmp_line);
		else if (verif_dollarcase(tmp_line) == 3)
			line = var_false(tmp_line);
		tmp_line = ft_strdup(line);
		nb_dollar--;
	}
	free(tmp_line);
	return (line);
}
