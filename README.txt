TP 4 C++
Analyseur de logs apache

par Marie Guillevic et Maxence Drutel (B3207)

---

Mode d'emploi de l'application :

1) Créer l'application analog dans le dossier bin avec le Makefile ("make" ou "make analog")

2) Pour exécuter l'application : "./analog nomFichier.log" va afficher le top 10 des pages les plus consultées
Différentes options d'analyse peuvent être renseignées :

	"-t heure" : Ne récupère que les logs générés dans l'heure renseignée
	"-g nomGraph.dot" : Génère le graphique liant Referer et Targets pour le fichier log.
			    dans un fichier cible .dot
	"-e" : Exclut les logs avec pour target des images, du css ou du javascript
	"-ip adresse" : Ne prend en compte que les requêtes émises par l'IP renseignée
	"-err" : Permet d'analyser les requêtes dont le return code est différent de 200
	"-p min" : Conserve les requêtes dont la quantité de donnée renseignée est supérieur
		   au minimum renseigné (en octets)
	"-os nom" : Conserve les requêtes émises par un système d'exploitation renseigné (Windows, Linux...)

Exemples :
"./analog anonyme.log" : affiche le top 10 pour toutes les requêtes du fichier anonyme.log
"./analog -os Linux -t 10 -g graphe.dot anonyme.log" : affiche le top 10 et crée le graphique des referers/targets 
pour les requêtes émises par une OS linux entre 10h et 11h
"./analog -e -p 10000 anonyme.log" : affiche le top 10 des requêtes de plus de 10mo 
ne ciblant pas des images, du css ou du javascript

3) Un jeu de sept tests automatisés est disponible dans le dossier Tests afin de valider 
les différentes fonctionalités de l'application. Pour effectuer les tests, se rendre dans le dossier et
exécuter le script mktest.sh


Merci de votre lecture et bonne analyse !