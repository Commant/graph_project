==================================
====== Pour lancer le projet =====
==================================

Se placer dans le répertoire du projet et lancer les commandes:

>>make
>>./robot <vitesse rotation> <coordonees.txt>

------------Exemple------------

(simulation avec un robot de vitesse de rotation 42 rad/s et un jeu de donnée contenu dans un fichier coords.txt)

>>make
>>./robot 42 coords.txt

---------------------------------

Par défaut, la vitesse de rotation est de 2 rad/s et le jeu de donnés est contenu dan le fichier coords.txt.
Ainsi, pour lancer une simulation customisée, on peut aussi changer le jeu de sommets directement dans le fichier coords.txt et lancer:

>>make
>>./robot <vitesse rotatation>