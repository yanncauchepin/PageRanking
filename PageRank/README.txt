# Utilisation de transi.r

	- Ouvrir transi.r avec RStudio
	- Changer le répertoire courant (de base étant celui de transi.r)
	- Changer le chemin vers le fichier .tsv ( de base étant ./wikispeedia_paths-and-graph/paths_finished.tsv)
	- Exécuter le programme : crée en sortie un fichier transi.txt contenant la matrice de transition (temps d'exécution avec paths_finished.tsv ~ 3 min)
	- transi.txt comporte en première ligne le nom de chaque noeud puis une matrice carrée de transition

# Utilisation de main.c
	
	- Compiler le code : gcc main.c -lm
	- Lancer l'executable : 
		Windows : .\a.exe {chemin vers transi.txt}
		  Linux : ./a.out {chemin vers transi.txt}
	- Saisie des paramètres :
		- Saisie de Bêta (réel)
		- Saisie du critère de précision (entier) de convergence du vecteur entre deux itérations (10^{-critère saisi}) selon la norme 1 (somme de la valeur absolue des écarts)
		- Choix entre Pagerank classique (0) ou Pagerank Personnalisé (1)
			- Si (1) :
				- Saisie du nombre de pages à personnaliser (entier)
				- Saisie des indices des pages à personnaliser (entier) un à la fois
		- Affichage dans la console du numéro de l'itération et de la norme 1 entre le vecteur à l'itération courante et celle précédente
		- Affichage dans la console des 20 noeuds ayant les rangs les plus élevés
		- Création / Modification d'un fichier vecteur.txt contenant le rang de chaque noeud sous le format "{Nom du noeud}" "{Rang du noeud associé}"
		