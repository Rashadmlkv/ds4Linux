CC = gcc
FLAGS = -std=gnu18 -Wall -Wextra -Werror -iquote $(HEADER) -o $(DAEMON) $(SOURCE)
HEADER = hdr/dmn/
SOURCE = src/dmn/*.c
DAEMON = ds4Linux_dmn

DAEMON:
	$(CC) $(FLAGS) -lbluetooth
clean:
	rm ds4Linux_dmn
