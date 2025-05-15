#include "ds4linux.h"

/*
 * newDaemon - object constructor
 * 
 * return: struct pointer
 */
Daemon* newDaemon(void) {

	printf("Allocating daemon\n");
	Daemon* newdaemon = malloc(sizeof(Daemon));

	if (newdaemon)
		initDaemon(newdaemon);

	return newdaemon;
}

/*
 * initDaemon - object initializer
 *
 * @self: struct pointer
 */
void initDaemon(Daemon* self) {

	printf("Initializing daemon\n");
	memset(self, 0, sizeof(Daemon));
        self->daemonize = &daemonize;
        self->prioritize = &prioritize;
}

/*
 * deleteDaemon - object destructor
 *
 * @self: struct pointer
 */
void deleteDaemon(Daemon* self) {

        printf("Deleting daemon\n");
        free(self);
}

/*
 * daemonize - daemonizing process
 *
 * @self: struct pointer
 */
void daemonize(Daemon* self) {

	printf("Daemonizing process\n");
	self->pid = getpid();
}


/*
 * prioritize - setting process pritority
 *
 * @self: struct pointer
 * @value: priority value
 */
void prioritize(Daemon* self, int8_t value) {

	(void)self;
	printf("Setting priority of process\n");
	errno = 0;
	nice(value);
}
