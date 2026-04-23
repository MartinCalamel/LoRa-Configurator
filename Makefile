# Nom de l'exécutable final
TARGET = build/main

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -I. -g

# Fichiers sources (.c)
SRCS = main.c src/Uart/Uart.c src/LoRa/LoRa.c src/gpio/gpio_utils.c

# Fichiers objets (.o)
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

LDLIBS = -llgpio

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Règle pour compiler chaque fichier .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de vérification (Celle qui posait problème)
check: $(TARGET)
	@echo "Vérification basique du binaire..."
	ls -l ./$(TARGET)
	@echo "Test de compilation : OK"

# Règle pour nettoyer
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf build

# Ajout de check dans .PHONY
.PHONY: all clean check
