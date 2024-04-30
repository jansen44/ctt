PROJECT=ctt
CC=gcc
CFLAGS=-Wall

TARGET_DIR=target
OBJ_DIR=$(TARGET_DIR)/obj
TARGET=$(TARGET_DIR)/$(PROJECT)

SRC=$(wildcard src/*.c)

_OBJ=$(patsubst src/%.c, %, $(SRC))
OBJ=$(patsubst %, $(OBJ_DIR)/%.o, $(_OBJ))

build: $(TARGET_DIR) $(OBJ_DIR) $(_OBJ) link

link: $(OBJ) 
	gcc -o $(TARGET) $^ 

$(_OBJ): $(SRC) 
	gcc -c -o $(OBJ_DIR)/$@.o src/$@.c $(CFLAGS)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -Rf $(OBJ_DIR)
	rm -Rf $(TARGET_DIR)

