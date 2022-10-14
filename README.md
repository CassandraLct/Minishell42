# Minishell42

------Regles Communes-------

	• Votre projet doit être écrit en C.
	• Votre projet doit être codé à la Norme. Si vous avez des fichiers ou fonctions bonus, celles-ci seront 	inclues dans la vérification de la norme et vous aurez 0 au projet en cas de faute de norme.
	• Vos fonctions de doivent pas s’arrêter de manière inattendue (segmentation fault, bus error, double 		free, etc) mis à part dans le cas d’un comportement indéfini. Si cela arrive, votre projet sera 			considéré non fonctionnel et vous aurez 0 au projet.
	• Toute mémoire allouée sur la heap doit être libéré lorsque c’est nécessaire. Aucun leak ne sera 		toléré.
	• Si le projet le demande, vous devez rendre un Makefile qui compilera vos sources pour créer la sortie 		demandée, en utilisant les flags -Wall, -Wextra et -Werror. Votre Makefile ne doit pas relink.
	• Si le projet demande un Makefile, votre Makefile doit au minimum contenir les règles $(NAME), all, clean, 	fclean et re.
	• Pour rendre des bonus, vous devez inclure une règle bonus à votre Makefile qui ajoutera les divers 			headers, librairies ou fonctions qui ne sont pas autorisées dans la partie principale du projet. Les 		bonus doivent être dans un fichier différent : _bonus.{c/h}. L’évaluation de la partie obligatoire et 	de la partie bonus sont faites séparément.
	• Si le projet autorise votre libft, vous devez copier ses sources et son Makefile associé dans un dossier 	libft contenu à la racine. Le Makefile de votre projet doit compiler la librairie à l’aide de son 		Makefile, puis compiler le projet.
	• Nous vous recommandons de créer des programmes de test pour votre projet, bien que ce travail ne sera pas 	rendu ni noté. Cela vous donnera une chance de tester facilement votre travail ainsi que celui de vos 		pairs.
	• Vous devez rendre votre travail sur le git qui vous est assigné. Seul le travail déposé sur git sera 		évalué. Si Deepthought doit corriger votre travail, cela sera fait à la fin des peer-evaluations. Si 	une erreur se produit pendant l’évaluation Deepthought, celle-ci s’arrête.

------Partie Obligatoire-----
![Screen Shot 2022-10-14 at 10 59 56 AM](https://user-images.githubusercontent.com/90134090/195809050-7219dd8e-3d77-4a3b-b855-2f5ff8dd27a7.png)

->Votre shell doit :
    • Afficher un prompt en l’attente d’une nouvelle commande.
    • Posséder un historique fonctionnel.
    • Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement PATH, ou sur un
        chemin relatif ou absolu).
    • Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez jus- tifier son utilisation.
    • Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).
    • Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets.
    • Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères présents dans la séquence entre guillemets sauf le $ (signe dollar).
	•Implémenter les redirections :
		◦ < doit rediriger l’entrée.
		◦ > doit rediriger la sortie.
		◦ << doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
		◦ >> doit rediriger la sortie en mode append.
	• Implémenter les pipes (caractère |). La sortie de chaque commande de la pipeline
	est connectée à l’entrée de la commande suivante grâce à un pipe.
	• Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
	qui doivent être substituées par leur contenu.
	• Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan.
	• Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
	• En mode interactif :	
		◦ ctrl-C affiche un nouveau prompt sur une nouvelle ligne. ◦ ctrl-D quitte le shell.
		◦ ctrl-\ ne fait rien.
	• Votre shell doit implémenter les builtins suivantes :
		◦ echo et l’option -n
		◦ cd uniquement avec un chemin relatif ou absolu ◦ pwd sans aucune option
		◦ export sans aucune option
	◦ unset sans aucune option
	◦ env sans aucune option ni argument
	◦ exit sans aucune option
->La fonction readline() peut causer des fuites de mémoire. Vous n’avez pas à les gérer. Attention, cela ne veut pas pour autant dire que votre code, oui celui que vous avez écrit, peut avoir des fuites de mémoire.

![Screen Shot 2022-10-14 at 11 06 33 AM](https://user-images.githubusercontent.com/90134090/195809147-5d110a62-0b5c-480d-b630-c00631e94988.png)

------Potentiel Bonus-------

/!\ si partie obligatoire parfaite /!\

![Screen Shot 2022-10-14 at 11 00 19 AM](https://user-images.githubusercontent.com/90134090/195809108-25d8acc7-5014-4f85-bb26-81015dcf214f.png)

