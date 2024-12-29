CC = gcc
CFLAGS = -Wall -g
INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
EXEC = file_manager

# Kaynak dosyalarınızı belirleyin
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/file_operations.c $(SRC_DIR)/directory_ops.c $(SRC_DIR)/permissions.c $(SRC_DIR)/logger.c
# Nesne dosyalarını belirleyin
OBJ = $(SRC:.c=.o)

# Hedef: file_manager
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Herhangi bir .c dosyasını .o dosyasına dönüştürme
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Temizleme komutu
clean:
	rm -f $(OBJ) $(EXEC)

