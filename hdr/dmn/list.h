#ifndef LIST_H
#define LIST_H
#include "gamepad.h"
#define GAMEPAD_CLASS 0x002508

typedef struct list {
	
	__attribute__((unused))Gamepad* gamepads;
	void (*append)(struct list* self, int8_t num_rsp, inquiry_info* inq_info); //wrapper
	int8_t (*find)(inquiry_info* inq_info); //find gamepad in inquiry_info    
	int8_t (*check) (struct list* self, bdaddr_t* bdaddr); //check gamepad already in list
	void (*add) (struct list* self, bdaddr_t bdaddr); //append new gamepad to list
	void (*rmv) (struct gamepad* node); //remove gamepad from list
} List;

void append (List* self, int8_t num_rsp, inquiry_info* inq_info);
int8_t find (inquiry_info* inq_info);
int8_t check (struct list* self, bdaddr_t* bdaddr);
void add (struct list* self, bdaddr_t bdaddr);
void rmv (struct gamepad* node);
List* newList (void);
#endif
