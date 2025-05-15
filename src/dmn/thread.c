#include "ds4linux.h"

Thread* newThread(void) {

	printf("Allocating thread\n");
	Thread* newthread = malloc(sizeof(Thread));

	initThread(newthread);

	return (newthread);
}

void initThread(Thread* self) {

	printf("Initializing thread\n");
	memset(self, 0, sizeof(Thread));
	self->create = &createThread;
	self->close = &closeThread;
	self->dev_mod_IO = &dev_mod_IO;
}

void deleteThread(Thread* self) {

	printf("Deleting thread\n");
	free(self);
}

void createThread(Thread* self, Gamepad* gamepad) {

	printf("Creating thread\n");
	self->args.thread = self;
	self->args.gamepad = gamepad;
	pthread_create(&self->id, NULL, self->dev_mod_IO, &self->args);
}

void closeThread(Thread* self) {

	(void)self;
	printf("Closing thread\n");
	pthread_exit(0);
}

void* dev_mod_IO(void* args) {

	printf("Performing io operations\n");
	Thread* thread = ((struct arguments *)args)->thread;
	Gamepad* gamepad = ((struct arguments *)args)->gamepad;

	(void)thread;	
	while (1){

		gamepad->recv(gamepad);
	}
}
