#include "ds4linux.h"

/*
 * newThread - object constructor
 *
 * return: struct pointer
 */
Thread* newThread(void) {

	printf("Allocating thread\n");
	Thread* newthread = malloc(sizeof(Thread));

	initThread(newthread);

	return (newthread);
}

/*
 * initThread - object initializer
 *
 * @self: thread object
 */
void initThread(Thread* self) {

	printf("Initializing thread\n");
	memset(self, 0, sizeof(Thread));
	self->create = &createThread;
	self->close = &closeThread;
	self->dev_mod_IO = &dev_mod_IO;
}

/*
 * deleteThread - object destructor
 *
 * @self: thread object
 */
void deleteThread(Thread* self) {

	printf("Deleting thread\n");
	free(self);
}

/*
 * createThread - creates new thread
 *
 * @self: thread object
 * @gamepad: gamepad object
 */
void createThread(Thread* self, Gamepad* gamepad) {

	printf("Creating thread\n");
	self->args.thread = self;
	self->args.gamepad = gamepad;
	pthread_create(&self->id, NULL, self->dev_mod_IO, &self->args);
}

/*
 * closeThread - exits from thread
 *
 * @self: thread object
 */
void closeThread(Thread* self) {

	(void)self;
	printf("Closing thread\n");
	pthread_exit(0);
}

/*
 * dev_mod_IO - IO operations between device & module
 *
 * @args: struct of gamepad & module objects
 */
void* dev_mod_IO(void* args) {

	printf("Performing io operations\n");
	Thread* thread = ((struct arguments *)args)->thread;
	Gamepad* gamepad = ((struct arguments *)args)->gamepad;

	(void)thread;	
	while (1){

		gamepad->recv(gamepad);
	}
}
