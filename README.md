# Minishell : Projet de gourpe

Le but de ce projet de 42 est de "recreer" un shell ayant le meme comportement que bash.

Avant de se lancer, il faut avant tout faire beaucoup de documentation sur tous les cas possibles et immaginable !

Nous avons dû recreer certains Built-in : Export, Unset, Cd, Exit, Echo (avec son option -n), Pwd, Env; 
changer le comportement des signaux, gerer les multi-pipes, les simples et double cotes,
la gestion du $? et $+var_globales ainsi que les redirections. Les "\" , les cotes non fermer 
et le ";" ne sont pas a gerer mais leur presence ne doit pas creer d'erreur de type segfault, etc.

Utiliser les fonctions de la librairie readline, revoir des notions déjà vu dans d'autres projets, 
reussir a comprendre le fonctionnement des multipipes et la logique de bash qui parfois n'est pas des plus
compréhensible a premiere vue...

