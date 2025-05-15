#include "ds4linux.h"


/*
 * newHci - object constructor
 * 
 * return: struct pointer
 */
Hci* newHci(void) {

	printf("Allocating hci\n");
	Hci* newhci = malloc(sizeof(Hci));

	if (newhci)
		initHci(newhci);

	return (newhci);
}

/*
 * initHci - object initializer
 *
 * @self: Local bluetooth adapter object
 */
void initHci(Hci* self) {

	printf("Initializing hci\n");
	memset(self, 0, sizeof(Hci));
	self->inquiry = &inquiry;
	self->id = hci_get_route(NULL);
}

/*
 * deleteHci - object destructor
 *
 * @self: Local bluetooth adapter object
 */
void deleteHci(Hci* self) {

	printf("Deleting hci\n");
	free(self->inq_info);
	free(self);
}


/*
 * inquiry - search nearby bluetooth devices
 *
 * @self: Local bluetooth adapter object
 */
void inquiry(Hci* self) {

	printf("Inquirying devices\n");
	self->num_rsp = hci_inquiry(self->id,\
		       	LEN,\
		       	MAX_RSP,\
		       	NULL,\
		       	&self->inq_info,\
		       	IREQ_CACHE_FLUSH);
}
