#include "dmn.h"


int
main (void) {

	Hci* bdev = newHCI();
	List* list = newList();


	bdev->inquiry(bdev); //search
	list->append( list, bdev->num_rsp, bdev->inq_info); //add to list

	return (0);
}
