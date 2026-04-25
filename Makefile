SRC_DIR = src
OBJ_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
HEADERS = $(wildcard include/*.h)

TARGET = build/app

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -Wall -Iinclude -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	gcc -Wall -Iinclude -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean : 
	rm -rf $(OBJ_DIR)

render : clean $(TARGET)
	$(TARGET) > $(OBJ_DIR)/image.ppm
	code $(OBJ_DIR)/image.ppm

.PHONY : all clean render
