# Projet LO21 - UTC A23
Projet de LO21 - UTC A23 - sur le jeu Splendor Duel (Marc André, Bruno Cathala)

Ce projet est réalisé par 
* Théo Guegan
* Samuel Manchajm
* Samuel Beziat
* Robert Antaluca
* Maxime Gautrot

Voici une petite vidéo présentant le projet :


[[SplendorDuel LO21]](https://youtu.be/C3SE0VFJZ7A)



Conseils pour compiler le projet sur Qt :
Cloner le répertoire sur votre machine, ouvrez le .pro avec Qt. Dans les paramètres d'exécution (rubrique 'Projets' sur le côté) pensez à décocher le 'shadow build' (dans 'Compiler') et à mettre comme répertoire d'exécution le dossier source, c'est à partir de ce fichier que les chemins relatifs fonctionnent.
Vous n'avez ensuite plus qu'à compiler et exécuter.

Nous conseillons vivement pour l'utilisation du mode IA vs IA de le lancer dans un autre terminal que celui de Qt car celui-ci limite grandement la vitesse des outputs.
Pour comparaison, sur un terminal externe Mac le mode IA vs IA se termine instantanément tandis qu'il prend du temps sur Qt.

Application testée sur Mac et sur Windows, non testée sur Linux.

Nous supposons qu'il reste certains bugs notamment dans le mode graphique puisque les parties sont longues et il est difficile d'aller chercher tous les problèmes.

Pour la partie console, nous avons lancé de nombreuses parties en mode IA vs IA et elles n'ont jamais crash depuis nos dernières modifications.

Pour tout problème, vous pouvez nous contacter une de nos adresses : prenom.nom@etu.utc.fr
