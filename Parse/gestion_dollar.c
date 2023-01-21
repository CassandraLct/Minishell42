/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:51:02 by clecat            #+#    #+#             */
/*   Updated: 2023/01/21 19:51:35 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
//change le $?
char	*var_reterr(char *line)
{
	printf("dans var_reterr, line = %s\n", line);
	if (line[0] == '$' && ft_strlen(line) == 2)
	{
		free(line);
		line = ft_strdup(ft_itoa(g_mini.ret_err));
	}
	printf("sortie var_reterr, line = %s\n", line);
	return (line);
}

//change la val de la var existante
char	*var_true(char *line)
{
	printf("dans var_true, line = %s\n", line);
	return (line);
}

//supprime la var non-existante de la line
char	*var_false(char *line)
{
	printf("dans var_false, line = %s\n", line);
	if (line[0] == '$' && line[4] == '\0')
	{
		free(line);
		line = NULL;
	}
	else
		printf("autres cas\n");
	printf("sortie var_false, line = %s\n", line);
	return (line);
}

//redirection vers les fonctions de modifications +25lignes
char	*change_line(char *line, int nb_dollar)
{
	char	*tmp;

	while (nb_dollar != 0)
	{
		tmp = ft_strdup(line);
		free(line);
		if (verif_dollarcase(line) == 1)
		{
			line = var_reterr(tmp);
			free(tmp);
			nb_dollar -= 1;
		}
		else if (verif_dollarcase(line) == 2)
		{
			line = var_true(tmp);
			free(tmp);
			nb_dollar -= 1;
		}
		else if (verif_dollarcase(line) == 3)
		{
			line = var_false(tmp);
			free(tmp);
			nb_dollar -= 1;
		}
	}
	return (line);
}

char	*rm_multispace(char *line, char *new_line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == 32)
		i++;
	while (line[i])
	{
		while (line[i] >= 33 && line[i] <= 126)
		{
			new_line[j] = line[i];
			j++;
			i++;
		}
		if (line[i] == 32 && (line[i + 1] >= 33 && line[i + 1] <= 126))
		{
			new_line[j] = line[i];
			j++;
			i++;
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
