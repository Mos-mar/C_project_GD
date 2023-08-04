# C_learning_journey
#Projet Lib GD
Écrire en C un programme qui génère un graphique de type Pie Chart en utilisant la libraire GD.

#
Le programme sera lancé en ligne de commande et permettra
=> l’entrée d’un jeu de pourcentages accompagné d’étiquettes optionnelles qui seront
affichées sur le graphique
=> de donner le nom du fichier de sortie au format png
Le programme sera réalisé avec la librairie GD écrite en C dont la documentation
est disponible à l’adresse https://libgd.github.io/
#
/* Énoncé : Trois int puis trois string et nommage string en argument ./programme
argument lors de l'appel de la fonction

pie -p 40,50,10 -l USA,CANADA,FRANCE output.png

pie -p 40,50,10 -l USA,CANADA,FRANCE -t histo output.png

*/

#
La librairie GD a été écrite en C mais a été rendue compatible avec les langages
PHP, Perl, Python, C++.

#Installation
Il faudra installer les librairies GD et math.h pour pouvoir compilé et lancer le programme.

Commande de lancement sur bash : gcc -o output main.c -lgd -lm
