🗡️ Zelda-like 2D RPG in C (Raylib)
Un RPG d'action 2D en C moderne (C99), développé de A à Z sans moteur de jeu. L'objectif principal de ce projet est la maîtrise de l'architecture logicielle, de la gestion manuelle de la mémoire, des pointeurs simples/doubles et des structures de données.
🎯 Objectifs Pédagogiques
Gestion Manuelle de la Mémoire : Allocation dynamique (malloc, realloc, free), prévention stricte des fuites mémoire et des dangling pointers.
Pointeurs & Pointeurs Doubles : Manipulation de matrices 2D dynamiques (Tile**), collections variables d'objets et d'entités (Entity**).
Structures de Données : Listes chaînées simples (InventoryNode*), machines à états finis.
Moteur Physique Custom : Collisions AABB axe-par-axe sur grille avec glissement fluide (style Zelda / Hades).
Architecture Modulaire : Encapsulation stricte, séparation header (.h) / implémentation (.c), principes SOLID en C.
🛠️ Technologies & Bibliothèques
Langage : C (Norme C99)
Bibliothèque Visuelle & Entrées : Raylib (uniquement pour la création de fenêtre, le rendu 2D et les entrées clavier)
Compilation : gcc / make
📂 Structure du Projet
.
├── main.c              # Point d'entrée du programme
├── game.h / game.c     # Gestionnaire principal de la boucle de jeu (Gameloop)
├── player.h / player.c # Entité Joueur, inputs et statistiques
├── map.h / map.c       # Génération, rendu et gestion de la carte 2D (Tile**)
├── physics.h / physics.c # Moteur physique (AABB, collisions grille, glissement)
├── item.h              # Énumération et structures des objets ramassables
├── inventory.h / .c    # Inventaire dynamique (Liste chaînée simple)
├── Makefile            # Script d'assemblage et de compilation automatique
└── README.md           # Documentation du projet


🚀 Avancement du Projet (Missions)
[x] Mission 1 : Squelette du Jeu, Encapsulation & Gameloop Minimal
[x] Mission 2 : Entité Joueur & Allocation Dynamique
[x] Mission 3 : Carte, Tuiles & Allocation 2D Dynamique (Tile**)
[x] Mission 4 : Moteur Physique & Collisions Axe-par-Axe (Glissement)
[x] Mission 5 : Inventaire & Liste Chaînée Simple (InventoryNode*)
[ ] Mission 6 : Gestionnaire d'Entités & Pointeurs Doubles (Entity**)
[ ] Mission 7 : Hitboxes d'Attaque, Portée d'Épée & Dégâts
[ ] Mission 8 : PNJs, Dialogues & Machine à États Finis (FSM)
[ ] Mission 9 : Cartes Multiples, Transitions & Zones
[ ] Mission 10 : Audit Mémoire (Valgrind / AddressSanitizer) & Polish Visuel
⚙️ Compilation et Exécution
Prérequis
Assure-toi d'avoir installé gcc, make et la bibliothèque Raylib sur ton système.
Linux (Ubuntu/Debian) :
sudo apt install build-essential libraylib-dev


macOS (Brew) :
brew install raylib


Commandes Makefile
Compiler le projet :
make


Compiler et lancer le jeu :
make run


Nettoyer les fichiers objets (.o) :
make clean


Nettoyage complet (.o + exécutable) :
make fclean


Recompiler à neuf :
make re



## License

No license specified. To make this project open source, add a LICENSE file (for example, MIT, Apache-2.0, or GPL-3.0) and update this section.

## Contact

If you have questions or ideas, open an issue or contact the repository owner.
