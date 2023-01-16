/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:55:54 by clecat            #+#    #+#             */
/*   Updated: 2023/01/16 10:54:10 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// a tester quand split line finie
//patern = chevron, verifier le premiers fichier existe sinon error ret_err = 1
//possibilité de donner un chemin (pour l'entree et la sortie);
//le fichier de sortie est creer si il n'existe pas
//chevron > stdout ne pas oublier de close une fois utiliser
void	right_patern(void)
{
	int	fd;

	fd = open(g_mini.tab, O_WRONLY | O_CREAT);
}

//chevron < stdin // si le fichier est un directory doit afficher 
//bash: TestDirectory: Is a directory
void	left_patern(void)
{
	int	fd;

	fd = open(g_mini.tab, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n");
		g_mini.ret_err == 1;
		exit(1);
	}
}

//chevron >> stdout, ecrit au niv EOF
void	dright_patern(void)
{
	int	fd;

	fd = open(g_mini.tab, O_RDWR | O_CREAT);
}

//chevron << (heredoc) peut etre utiliser sans cmd mais doit avoir un arg
//affiche l'erreur de grep / cat affiche ce qui a ete ecrit dans le heredoc
// le heredoc se lance avant la cmd puis une fois fermer la cmd est effectuer
//bash: syntax error near unexpected token `newline'
void	dleft_patern(void)
{
	int	fd;

	if (g_mini.tab[1] == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
}

/*comme le readline (boucle tant que le mot donné ne soit ecrit)*/
//	while (ft_strcmp(strline, arg) != 0)
//	{
//		tab[i] = strdup(str);
//		printf(">"); (recupere la line apres le chevron);
//		i++;
//	}
//	des que c'est egal, donner en entrer de la commande avant si presente
//	ou affiche le msg d'erreur de la cmd si n'a pas d'arg (gerer par execve?)
