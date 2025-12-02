# Nom de l'exécutable
TARGET = morpion.exe

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Fichiers sources
SRC = main.c morpionDuo.c ordinateur.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle par défaut : tout compiler
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilation des fichiers objets
%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	@del /Q $(OBJ) $(TARGET) 2>nul
