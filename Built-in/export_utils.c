/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:35:49 by clecat            #+#    #+#             */
/*   Updated: 2022/11/23 19:00:02 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions

//compare la taille de 2 char**
int	tablen(t_min mini)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (mini.c_env[i])
		i++;
	while (mini.c_exp[y])
		y++;
	if (y != i)
		return (1);
	return (0);
}

//verifie si index envoyer est deja present dans copy exp
int	check_exp(t_min mini, int index)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
	{
		if (strcmp(mini.c_env[index], mini.c_exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//copie env ds exp dans l'ordre ascii
void	fill_exp(t_min mini, char *str)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
		i++;
	mini.c_exp[i] = ft_strdup(str);
	mini.c_exp[i + 1] = NULL;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(sizeof(*s1) * (i + j + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

//print export with "declare-x" & valeur entre ""
void	print_export(t_min mini)
{
	int		i;
	int		y;
	int		index;

	i = 0;
	y = 0;
	while (mini.c_exp[i])
	{
		printf("declare -x ");
		while (mini.c_exp[i][y] != '=')
			printf("%c", mini.c_exp[i][y++]);
		printf("%c%c", mini.c_exp[i][y], 34);
		index = y + 1;
		while (mini.c_exp[i][index] != '\0')
			printf("%c", mini.c_exp[i][index++]);
		printf("%c\n", 34);
		y = 0;
		i++;
	}
}
