CC = gcc
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
APP = basicbash
SOURCES = $(wildcard $(SRC_DIR)/*.c) # get all .c files in the SRC_DIR
# create corresponding object files list
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS = -g -Wall

# all, directories are not actually files we will create
.PHONY: all directories

all: directories $(APP)

# link OBJECTS to the APP executable
$(APP): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

directories:
	mkdir -p $(OBJ_DIR)

# rule for each object. Take the source file, compile it to a .o file in the
# OBJ_DIR
# $< is the first prerequisite (ie, the source file)
# $@ is the target (ie, the object file)
# see more here: https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

# this is an implicit rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# we could also do this static rule
# $(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(APP)
