# SatelliteF429
Le but de ce code est de s'initier aux microcontrolleur STM32 sur une carte de développement NUCLEO-F429ZI. Le tout dans un contexte de développement sous FreeRTOS
## Étapes d'utilisation
Voici les étapes a effectuer pour utiliser ce projet:
1. Installer les outils de développement STM32CubeIDE (et éventuellement STM32CubeMonitor)
2. Ouvrir STM32CubeIDE
3. J'assume que vous connaissez GIT, il faut cloner le projet a une endroit de votre choix
4. Dans STM32CubeIDE cliquer sur File > Import... > General > Existing project into Workspace puis choisir le projet a l'endroit ou vous l'avez mis
5. Connecter la carte de développement a votre ordinateur par le port micro USB B nommé CN1
6. Cliquer sur le petit insecte dans le haut du projet, cela va lancer une session de Debug (Il est possible que le ST-LINK it besoins d'une mise a jour, faites-la au cas ou cela vous est demandé)
7. Le code devrait maintenant s'éxecuter sur la carte de développement (LD1, LD2 et LD3 vont clignoté)

## Explication du code
Le code sur le satellite utilise FreeRTOS, un système d'exploitation sur microcontrolleur, toutefois, pour notre utilisations, on veut prendre qu'un seul Thread, donc ce que l'on appel une Super-Loop. L'entièreté du code pour le projet du Satellite se trouvera dans UserTask.h et UserTask.c, ce sera les deux seuls fichier qui auront besoins d'etre modifier. Bien entendu d'autre fichier s'ajouterons, mais seront toujours utiliser dans UserTask.h et UserTask.c

Pour l'instant la première tache, simule le code du satellite d'Endurosat, ce code a chaque seconde fait clignoter la led LD3 rouge, si cette LED ne clignote pas, le code d'Endurosat ne s'éxécute pas et c'est problématique, cette LED doit clignoter en tout temps. Les deux autres LEDs sont dans le Thread UserTask.c cette boucle s'effectue au 5 ms mais les LEDs clignote pour LD2 au secondes et LD1 au quart de secondes. Ces deux leds clignote sans bloquer le Thread, ce qui est vital pour notre satellite. Je vais expliquer pourquoi en personne.

## Les fichier .ioc
Les fichiers .ioc définisse le Hardware de manière visuel, il ne faut pas manipuler de logique directement, ce qui est plus simple pour nous, il est important que les pins aient le même nom que ceux d'Endurosat, ce qui va faciliter le transition entre ce code et celui de l'OBC. Il est possible que vous ayez a modifier ce fichier, simplement cliquer dessus et vous verrez de quoi ca a l'air.