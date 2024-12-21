CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = main.o text_operations.o regex_operations.o
TARGET = sed_simplified

all: $(TARGET)

$(TARGET): $(OBJ)
	    $(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	    rm -f $(OBJ) $(TARGET)

test:
	    ./$(TARGET) input.txt 's/old_text/new_text/'
	        ./$(TARGET) input.txt '/pattern/d'
		    ./$(TARGET) input.txt 's/^/prefix/'
		        ./$(TARGET) input.txt 's/$/suffix/'

.PHONY: clean test
