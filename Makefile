CC = gcc
FLAGS = -o $(DAEMON) -Wall -Wextra -Werror -std=gnu18
DIR = src/dmn/*.c hdr/dmn/*.h
DAEMON = ds4Linux_dmn

DAEMON: src/dmn/*.c hdr/dmn/*.h
	$(CC) $(FLAGS) $(DIR) -lbluetooth
clean:
	rm ds4Linux_dmn
