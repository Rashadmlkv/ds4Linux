#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

struct arguments {

                struct thread* thread;
                Gamepad* gamepad;
};

typedef struct thread {

	struct thread* next;
	struct arguments args;
        void(*create)(struct thread* self, Gamepad* gamepad);
        void(*close)(struct thread* self);
        void*(*dev_mod_IO)(void* args);
	pthread_t id;
} Thread;

Thread* newThread(void);
void initThread(Thread* self);
void deleteThread(Thread* self);
void createThread(Thread* self, Gamepad* gamepad);
void closeThread(Thread* self);
void* dev_mod_IO(void* args);

#endif
