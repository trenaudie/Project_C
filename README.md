# Project_C
dépôt github de mon projet C++. Date: 20 Janvier 2022

README - Projet C++ Tanguy RENAUDIE

Ce projet utilise un fichier main() dans lequel je mets tous les "include": #include "Matrix.hpp" #include "Euler1.hpp" #include "Gradient.hpp" #include "Euler2.hpp" #include "Euler3.hpp"

Le fichier "Matrix.hpp" introduit la classe Matrix et les fonctions display. La classe Matrix ne possède en attributs qu'un long vector 1-dimensionnel de valeurs, ainsi qu'une valeur pour le nb de lignes et une valeur pour le nb de colonnes. On implémente toutes les méthodes opérations: add substract multiply, qui font l'opération en modifiant l'objet. On implémente aussi toutes les fonctions opérations avec les opérateurs * + -. Elle retournent le résultat sous la forme d'une nouvelle matrice.

Le fichier "Euler1.hpp" répond à la question 2. C'est la méthode d'Euler explicite. Le fichier "Gradient.hpp" répond à la question 3. C'est la méthode du gradient conjugué. Le fichier "Euler2.hpp" répond à la question 4. C'est la méthode d'Euler implicite. Le fichier "Euler3.hpp" répond à la question 5. C'est la méthode d'Euler explicite, mais avec un vecteur D généré d emanière aléatoire.

Discussion du choix de dx: Souvent je prends dx = 0.15 ce qui me donne un vecteur T^(k) à l'instant k de shape (1,7) Enfin on remarque que plus dx est faible (par exemple dx = 0.01), plus le système a tendance à diverger. Dans tous les cas, je n'ai que des divergences après un temps donné (environ 0.4 secondes, mais ça dépend du paramètre dx choisi)

Discussion du choix de dt: Souvent je prends dt = 0.001 ce qui donne une bonne précision sans être trop long pour le compilateur.

Pour utiliser ce répo, il suffit d'aller dans main, et de de-comment les commentaires. Compiler puis Exécuter. Les valeurs pour le temps et la température apparaissent dans des fichiers pythons temperature.txt et time.txt. Ensuite, j'ai codé un fichier "python_plotting.py" qui permet de plotter ces données.
