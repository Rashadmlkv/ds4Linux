#include "dmn.h"

/*
 * newList - allocates memorf for new List object
 *
 * return: newly allocated address
 */
List* newList (void) {
 
	List* newlist = malloc(sizeof(List));
	__attribute__((unused))Gamepad* gamepads = NULL;
	newlist->append = &append;
	newlist->find = &find;
	newlist->check = &check;
	newlist->add = &add;
	newlist->rmv = &rmv;
	return (newlist);
}

/*
 * append - wrapper for adding node to list
 *
 * @self: a list object
 * @num_rsp: number of devices got in inquiry
 * @inq_info: linked list of found devices
 */
void append (struct list* self, int8_t num_rsp, inquiry_info* inq_info) {

	for (int8_t i = 0; i < num_rsp; i++) {

		//gamepad found and is not in list, add to list
		if (!(self->find(inq_info + i)) &&\
				!(self->check(self,&(inq_info + i)->bdaddr))) {

			self->add(self, (inq_info + i)->bdaddr);
		}
	}
}

/*
 * find - find controller from list
 *
 * @inq_info: node of linked list
 * return: 0 is controller, -1 not
 */
int8_t find (inquiry_info* inq_info) {

	//device is gamepad
	if (GAMEPAD_CLASS == ((inq_info->dev_class[2] << 16)|\
				(inq_info->dev_class[1] << 8)|\
				(inq_info->dev_class[0])))
		return (0);
	else
		return (-1);
}

/*
 * check - checks controller with bdaddr is in list
 *
 * @self: a list object
 * @bdaddr: bluetooth address of gamepad
 * return: 0 is not in list, -1 is
 */
int8_t check (struct list* self, bdaddr_t* bdaddr) {

	//gamepads list is not empty
	if (self->gamepads) {
	
		char bdaddrstr[18];
		ba2str(bdaddr, bdaddrstr);
		Gamepad* tmp = self->gamepads;

		for (; tmp->next; tmp=tmp->next) {

			//already in list
			if (!(strcmp(bdaddrstr, tmp->bdaddrstr))) {

				return (-1);
			}
		}
	}
	return (0);
}

/*
 * add - adds node to list
 * 
 * @self: a list object
 * @bdaddr: bluetooth address of gamepad
 */
void add (struct list* self, bdaddr_t bdaddr) {

	if (!(self->gamepads)) {

		Gamepad* node = newGamepad();

		//object is created but connection failed
        	if (node && node->connect(node, bdaddr)) {
	
			self->rmv(node);
        	}
	} else {
	
		Gamepad* tmp = self->gamepads;
		
		while (tmp->next)
			tmp = tmp->next;

		Gamepad* node = newGamepad();

		//object is created but connection failed
		if (node && node->connect(node, bdaddr)) {

                        self->rmv(node);
                } else {
		
			tmp->next = node;
		}
	}
}

/*
 * rmv - removes gamepad from list
 *
 * @node: a gamepad object
 */
void rmv (struct gamepad* node) {

	node->disconnect(node);
	free(node);
}
