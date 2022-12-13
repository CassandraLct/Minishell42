/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:45 by clecat            #+#    #+#             */
/*   Updated: 2022/12/13 15:54:13 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_min
{
	char	**c_env;
	char	**c_exp;
	int		ret_err;
	char	*line;
	char	**tab;
	char	*prompt;
	char	*cdpath;
	int		nb_passage_exp;
}	t_min;

//15 fichiers
//utils.c 5 fonctions
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
int		strdigit(char *str);
int		ft_isdigit(char c);
char	*ft_strdup(char *s);

//ft_split.c (split libft)
char	**ft_split(char const *s, char c);

//env.c 1 fonction
void	ft_env(t_min mini);

//export.c 5 fonctions
t_min	export(t_min mini);
char	**order_exp(char **s1, char **s2);
int		verif_modif_var(char **str, char *cmp);

//export_utils.c 5 fonctions
void	print_export(char **str);
char	**fill_exp(char **new_val, char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		tablen(char **s1);
int		check_exp(char **s1, char **s2, int index);

//export_addvar.c 3 fonctions
char	**add_valexp(t_min mini, char *str);
char	**add_valenv(t_min mini, char *str);

//export_change_val 5 fonctions
char	*recup_name(char *cmp, char *name_var);
t_min	redir_changeval(t_min mini, char *str);

//echo.c 4 fonctions
void	echo(t_min mini);

//parse.c 4 fonctions
void	free_tab(char **tab);
char	**init_cpy(char **str, char **dest);
char	**ft_cpytab(char **tab);
char	**init_exp(char **tab);

//cd.c 5 fonctions
void	cd(t_min mini);

//exit_pwd.c 3 fonctions
int		exit_min(t_min mini);
void	pwd(char **c_env);

//init.c 3 fonctions
t_min	init_struct(t_min mini, char **envp);
char	**init_export(t_min mini);
void	free_all(t_min mini);

//unset.c 4 fonctions
t_min	unset(t_min mini);
int		check_var(char *str);

//exec.c 4 fonctions
void	ft_exec(t_min mini, char **all_path, char **cmd);
void	ft_set_pathexec(t_min mini);

//lexer.c 2 fonctions
char	**split_line(t_min mini);
t_min	redirection(t_min mini);

//signaux.c
void	signaux(void);

#endif