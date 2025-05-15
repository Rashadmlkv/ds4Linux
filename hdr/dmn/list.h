#ifndef LIST_H
#define LIST_H

#include "gamepad.h"
#include "thread.h"
#define GAMEPAD_CLASS 0x002508

typedef struct list {

	Gamepad* gamepads;
	Thread* threads;
        void(*append)(struct list* self, inquiry_info* inq_info, int8_t num_rsp);
        int8_t(*isGamepad)(uint8_t dev_class[]);
        int8_t(*compare)(struct list* self, bdaddr_t* bdaddr);
        int8_t(*addGamepad) (struct list* self, bdaddr_t bdaddr);
	int8_t(*addThread) (struct list* self, Gamepad* gamepad);
        void (*rmv) (struct gamepad* node);
} List;

List* newList(void);
void initList (List* self);
void deleteList(List* self);
void append(List* self, inquiry_info* inq_info, int8_t num_rsp);
int8_t isGamepad(uint8_t dev_class[]);
int8_t compare(List* self, bdaddr_t* bdaddr);
int8_t addGamepad (List* self, bdaddr_t bdaddr);
int8_t addThread(struct list* self, Gamepad* gamepad);
#endif
