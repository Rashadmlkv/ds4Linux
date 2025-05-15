#include "ds4linux.h"

Hci* newHci(void) {

	printf("Allocating hci\n");
	Hci* newhci = malloc(sizeof(Hci));

	if (newhci)
		initHci(newhci);

	return (newhci);
}

void initHci(Hci* self) {

	printf("Initializing hci\n");
	memset(self, 0, sizeof(Hci));
	self->inquiry = &inquiry;
	self->id = hci_get_route(NULL);
}

void deleteHci(Hci* self) {

	printf("Deleting hci\n");
	free(self->inq_info);
	free(self);
}

void inquiry(Hci* self) {

	printf("Inquirying devices\n");
	self->num_rsp = hci_inquiry(self->id,\
		       	LEN,\
		       	MAX_RSP,\
		       	NULL,\
		       	&self->inq_info,\
		       	IREQ_CACHE_FLUSH);
}
