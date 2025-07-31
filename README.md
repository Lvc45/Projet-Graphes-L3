# Projet-Graphes
# Mise en situation
Dans le cadre d’un projet de L3, j’ai participé au développement d’un programme visant à identifier le chemin critique d’un graphe, à partir d’un ensemble de contraintes exprimées en nombre de jours. Le graphe ainsi obtenu représente un calendrier de projet, dans lequel chaque tâche est modélisée comme un sommet, et les dépendances temporelles comme des arcs orientés. Ce programme permet de visualiser et d’optimiser la planification en identifiant les tâches clés qui déterminent la durée totale du projet.
# Fonctionnalités
Fonctionnalités principales du programme :
- Lecture d’un tableau de contraintes depuis un fichier .txt  
- Mise en mémoire et affichage du tableau à l’écran  
- Construction d’un graphe orienté représentant les dépendances entre tâches  
- Vérification de la validité du graphe (absence de circuits et d’arcs négatifs)  
- Calcul du calendrier au plus tôt pour chaque tâche  
- Détermination de la durée totale du projet  
- Calcul du calendrier au plus tard (avec contrainte de fin = début au plus tôt)  
- Calcul des marges totales et libres  
- Identification du ou des chemins critiques  
- Tri topologique des sommets du graphe (par rang croissant)  
