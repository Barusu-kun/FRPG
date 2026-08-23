==============================================================================
# Makefile Automatique & Modulaire pour Projet C / Raylib
==============================================================================

# Nom de l'exécutable final
TARGET = zelda_game

# Compilateur et flags de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g -MMD -MP

# Bibliothèques à lier (Raylib + dépendances système Linux/macOS)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	# macOS
	LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else
	# Linux / Autre
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Détection automatique de tous les fichiers .c dans le dossier
SRCS = $(wildcard *.c)

# Transformation de la liste de .c en .o (placés dans un dossier obj/ pour garder le projet propre)
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

==============================================================================
# Règles de Compilation
==============================================================================

# Règle par défaut
all: $(TARGET)

# Lien de l'exécutable
$(TARGET): $(OBJS)
	@echo "🔗 Liens de l'exécutable $@..."
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✨ Compilation réussie !"

# Compilation des fichiers objets (.o) et génération des dépendances (.d)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "🛠️ Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier d'objets si inexistant
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Inclusion automatique des dépendances des fichiers headers (.h)
-include $(DEPS)

# Exécuter le jeu directement
run: all
	@echo "🚀 Lancement de $(TARGET)"
	./$(TARGET)

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	@rm -rf $(OBJDIR)

# Nettoyage complet (fichiers objets + exécutable)
fclean: clean
	@echo "🗑️ Suppression de l'exécutable $(TARGET)..."
	@rm -f $(TARGET)

# Recompilation complète
re: fclean all

.PHONY: all run clean fclean re
