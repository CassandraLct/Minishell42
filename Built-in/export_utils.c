/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:35:49 by clecat            #+#    #+#             */
/*   Updated: 2022/11/28 16:38:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions

//compare la taille de 2 char**
int	tablen(char **s1, char **s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if(s2 == NULL)
		return (1);
	while (s1[i])
		i++;
	printf("s2[y] = %s\n", s2[y]);
	while (s2[y])
		y++;
	//printf("cmplen = %d, explen = %d\n", i, y);
	if (y != i)
		return (1);
	return (0);
}

//verifie si index envoyer est deja present dans copy exp
//cmp = env ou cpy
int	check_exp(char **cmp, char **c_exp, int index)
{
	int	i;

	i = 0;
	if(!c_exp || !cmp)
		return (0);
	while (c_exp[i])
	{
		//printf("cmp[index] = %s\n", cmp[index]);
		printf("test4\n");
		if (strcmp(cmp[index], c_exp[i]) == 0)
			return (1);
		printf("test5\n");
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
void	print_export(char **c_exp)
{
	int		i;
	int		y;
	int		index;

	i = 0;
	y = 0;
	while (c_exp[i])
	{
		printf("declare -x ");
		while (c_exp[i][y] != '=')
			printf("%c", c_exp[i][y++]);
		printf("%c%c", c_exp[i][y], 34);
		index = y + 1;
		while (c_exp[i][index] != '\0')
			printf("%c", c_exp[i][index++]);
		printf("%c\n", 34);
		y = 0;
		i++;
	}
}
