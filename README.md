# Minishell42 --- ReadMe en cours------

Le but de ce projet est de "recreer" un terminal meme comportement que bash.

Avant de se lancer, faire beaucoup de documentation sur tous les cas possibles et immaginable !

Pour ce projet en C, nous avons dû utiliser la librairie readline.

Nous avons dû recreer certains Built-in : Export, Unset, Cd, Exit, Echo (avec son option -n), Pwd, Env; 
changer le comportement des signaux, gerer les multi-pipes, les simples et double cotes,
la gestion du $? et $+var_globales ainsi que les redirections. Les "\" , les cotes non fermer 
et le ";" ne sont pas a gerer mais leur presence ne doit pas creer d'erreur de type segfault, etc.

->Votre shell doit :
    • Afficher un prompt en l’attente d’une nouvelle commande.
    • Posséder un historique fonctionnel.
    • Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement PATH, ou sur un
        chemin relatif ou absolu).
    • Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez justifier son utilisation.
 
->La fonction readline() peut causer des fuites de mémoire. Vous n’avez pas à les gérer. Attention, cela ne veut pas
	pour autant dire que votre code, oui celui que vous avez écrit, peut avoir des fuites de mémoire.

