/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:41:27 by clecat            #+#    #+#             */
/*   Updated: 2022/11/14 13:16:45 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//return: 1 = error; 0 = ok
#include <stdio.h>
#include <stdlib.h>

//cas simple cote et double cote, et si cote non fermer
//"" == 34, '' == 39
static int	cmp_nb_word(const char *s, char c)
{
	int	i;
	int	word;

	if (!s)
		return (0);
	word = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		if(s[i] == 34)
		{
			
		}
		while (s[i] && (s[i] != c))
			i++;
		word++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (word);
}

static int	cmp_nb_caract(const char *s, char c, char **str)
{
	int	n;
	int	i;
	int	x;

	n = 0;
	i = 0;
	x = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
		{
			i++;
			n++;
		}
		str[x] = malloc(sizeof(char) * (n + 1));
		if (!str)
			return (0);
		x++;
		n = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (0);
}

static void	ft_assembleall(char const *s, char c, char **str)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
		{
			str[x][y] = s[i];
			i++;
			y++;
		}
		str[x][y] = '\0';
		y = 0;
		x++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	str[x] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		x;
	int		y;

	x = 0;
	y = 0;
	str = malloc((sizeof(char *) * (cmp_nb_word(s, c) + 1)));
	if (!str)
		return (NULL);
	cmp_nb_caract(s, c, str);
	ft_assembleall(s, c, str);
	return (str);
}

//split dès qu'il y a un espace, -> ne pas split si il y a des cotes(""; '')
//verifier si il y a bien 2 cotes (debut/fin)
int main(int argc, char **argv)
{
	//char *line = "minishell> gcc main.c | grep "main" > test";//faire avec argv pour tester
	(void)argc;
	char **tab;
	int	x = 0;
	
	tab = ft_split(argv[1], ' ');
	while(tab[x] != NULL)
	{
		printf("%s\n", tab[x]);
		x++;
	}
}