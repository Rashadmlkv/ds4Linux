#include "ds4linux.h"

Daemon* newDaemon(void) {

	printf("Allocating daemon\n");
	Daemon* newdaemon = malloc(sizeof(Daemon));

	if (newdaemon)
		initDaemon(newdaemon);

	return newdaemon;
}

void initDaemon(Daemon* self) {

	printf("Initializing daemon\n");
	memset(self, 0, sizeof(Daemon));
        self->daemonize = &daemonize;
        self->prioritize = &prioritize;
}

void deleteDaemon(Daemon* self) {

        printf("Deleting daemon\n");
        free(self);
}

void daemonize(Daemon* self) {

	printf("Daemonizing process\n");
	self->pid = getpid();
}

void prioritize(Daemon* self, int8_t value) {

	(void)self;
	printf("Setting priority of process\n");
	errno = 0;
	nice(value);
}
