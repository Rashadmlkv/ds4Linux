#include "ds4linux.h"

/*
 * newList - object constructor
 * 
 * return: struct pointer
 */
List* newList(void){

	printf("Allocating list\n");
	List* newlist = malloc(sizeof(List));

	initList(newlist);

	return (newlist);
}

/*
 * initList - object initializer
 *
 * @self: list object
 */
void initList (List* self) {

	printf("Initializing list\n");
	memset(self, 0, sizeof(List));
        self->append = &append;
        self->isGamepad = &isGamepad;
        self->compare = &compare;
        self->addGamepad = &addGamepad;
	self->addThread = &addThread;
        //self->rmv = &rmv;
}

/*
 * deleteList - object destructor
 *
 * @self: list object
 */
void deleteList(List* self) {

	printf("Deleting list\n");
	Gamepad* temp = self->gamepads;
	for (; temp;) {

		self->gamepads = temp->next;
		deleteGamepad(temp);
		temp = self->gamepads;
	}
	free(self);
}

/*
 * append - wrapper for adding gamepad to list
 *
 * @self: list object
 * @inq_info: found nearby bluetooth devices
 * @num_rsp: count of found nearby bluetooth devices
 */
void append(List* self, inquiry_info* inq_info, int8_t num_rsp) {

	printf("Appending to list\n");
	for (uint8_t i = 0; i < num_rsp; ++i) {
	
		if (!(self->isGamepad((inq_info + i)->dev_class)) &&\
				!(self->compare(self, &(inq_info + i)->bdaddr))) {
			
			self->addGamepad(self, (inq_info + i)->bdaddr);
			self->addThread(self, self->gamepads);
		}
	}
}

/*
 * isGamepad - checks bluetooth device is gamepad
 * 
 * @dev_class: Class of bluetooth device
 */
int8_t isGamepad(uint8_t dev_class[]) {

	printf("Checking device class\n");
	if (GAMEPAD_CLASS == ((dev_class[2] << 16)|\
				(dev_class[1] << 8)|\
				(dev_class[0])))
		return (0);
	else
		return (-1);
}

/*
 * compare - checks gamepad is already in list
 *
 * @self: list object
 * @bdaddr: bluetooth address of gamepad
 *
 * return: -1 if in list, 0 if not
 */
int8_t compare(List* self, bdaddr_t* bdaddr) {

	printf("Comparing device\n");
	if (self->gamepads) {

		char bdaddrstr[19];
		ba2str(bdaddr, bdaddrstr);
		Gamepad* temp = self->gamepads;
		for (; temp->next; temp = temp->next) {
		
			if (!(strcmp(temp->bdaddr, bdaddrstr)))
				return (-1);
		}
	}
	return (0);
}


//This function and thread will be reformatted
/*
 * addGamepad - adds gamepad to list
 *
 * @self: list object
 * @bdaddr: bluetooth address of gamepad
 */
int8_t addGamepad (List* self, bdaddr_t bdaddr) {

	printf("Adding device to list\n");
	Gamepad* gamepad = newGamepad();

	gamepad->connect(gamepad, bdaddr);

	if (!(self->gamepads)) {
	
		self->gamepads = gamepad;
		gamepad->next = NULL;
	} else {
	
		gamepad->next = self->gamepads;
		self->gamepads = gamepad;
	}
	return (0);
}

/*
 * addThread - add thread to list
 *
 * @self: list object
 * @gamepad: gamepad object 
 */
int8_t addThread(List* self, Gamepad* gamepad) {

	Thread* thread = newThread();

	thread->create(thread, gamepad);

	if (!(self->threads)) {
	
		self->threads = thread;
		thread->next = NULL;
	} else {
	
		thread->next = self->threads;
		self->threads = thread;
	}
	return (0);
}
