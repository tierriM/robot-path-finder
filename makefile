CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC = src/grid.c src/pathfinder.c src/robot.c src/structures.c src/utils.c src/main.c
OBJ = $(SRC:.c=.o)
EXEC = robot_project

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
