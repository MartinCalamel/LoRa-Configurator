# Nom de l'exécutable final
TARGET = build/main

# Compilateur
CC = gcc

# Options de compilation
# -Wall : affiche tous les avertissements
# -Wextra : affiche encore plus d'avertissements
# -I. : permet de trouver les headers si tu fais #include "Uart/Uart.h"
CFLAGS = -Wall -Wextra -I. -g

# Fichiers sources (.c)
# On liste tous les fichiers nécessaires
SRCS = main.c Uart/Uart.c LoRa/LoRa.c

# Fichiers objets (.o)
# Cette ligne transforme automatiquement la liste des .c en .o
OBJS = $(SRCS:.c=.o)

# Règle par défaut (celle exécutée quand on tape 'make')
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Règle pour compiler chaque fichier .c en .o
# Le % est un caractère générique
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers temporaires
clean:
	rm -f $(OBJS) $(TARGET)

# Évite les conflits avec des fichiers qui porteraient le même nom que les règles
.PHONY: all clean

@echo "Vérification basique du binaire..."
@ls -l ./$(TARGET)
@echo "Test de compilation : OK"
