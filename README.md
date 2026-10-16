#  2D RPG in C

Un RPG d'action 2D en C, développé de A à Z sans moteur de jeu, basé sur l'architecture de jeux comme Zelda et Hades.

## Objectifs du Projet

- Gestion manuelle de la mémoire : allocation dynamique, prévention des fuites mémoire
- Manipulation de pointeurs et structures de données complexes
- Moteur physique custom avec collisions AABB
- Architecture modulaire et encapsulation stricte
- Apprentissage des principes de conception logicielle en C

## Technologies

- **Langage** : C
- **Graphisme & Entrées** : Raylib
- **Compilation** : gcc / make

## Structure du Projet

```
.
├── main.c              # Point d'entrée
├── game.h / game.c     # Boucle de jeu
├── player.h / player.c # Entité Joueur
├── map.h / map.c       # Carte 2D (Tile**)
├── physics.h / physics.c # Moteur physique
├── item.h              # Objets et structures
├── inventory.h / .c    # Inventaire (liste chaînée)
├── entity.h / .c       # entités
├── entity_manager.h /.c# gestionnaire d'entités
├── dialogue.h /.c      # systeme de dialogue
├── editeur_carte.html  # outil vibe-codé pour editer des maps rapidement dans mon format et en .csv
├── LICENSE             # License open-source du MIT
├── Makefile            # Compilation
├── README.md           # Cette documentation
└──assets/map/x.csv    # fichiers map en .csv
```

## Progression

- [x] Squelette du jeu et gameloop
- [x] Entité joueur et allocation dynamique
- [x] Carte 2D avec tuiles
- [x] Moteur physique et collisions
- [x] Inventaire avec liste chaînée
- [x] Gestionnaire d'entités
- [x] Attaque joueur et hitboxes
- [x] PNJs et dialogues
- [x] Cartes multiples
- [x] Chargement de texture du joueur
- [ ] Ennemis attaquent et poursuivent le joueur (W.I.P)
- [ ] Système de vie pour entitées et joueur
- [ ] Inclure infos d'ennemis dans les fichiers map pour differents ennemis a chaque map
- [ ] Import map état propre, copie pour ecriture d'état actuel dessus pour garder en memoire etat de la salle

## Installation & Compilation

### Prérequis

**Linux (Ubuntu/Debian)**
```bash
sudo apt install build-essential libraylib-dev
```

**macOS (Homebrew)**
```bash
brew install raylib
```

### Compilation

```bash
make          # Compiler
make run      # Compiler et lancer
make clean    # Nettoyer les .o
make fclean   # Nettoyer tout
make re       # Recompiler
```

## Licence

Ce projet est sous licence **MIT**. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Auteur

El Aidaoui Sierra Adam
