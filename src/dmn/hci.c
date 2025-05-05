#include "dmn.h"

/*
 * newHci - allocates memory for new Hci object
 *
 * return: newly allocated memory
 */
Hci* newHCI (void) {

        Hci* bd;

        bd = malloc( sizeof( Hci));
        bd->inq_info = malloc( sizeof( inquiry_info) * MAX_LEN);
        bd->id = hci_get_route( NULL);
        bd->num_rsp = 0;
        bd->inquiry = &inquiry;

        return (bd);
}

/*
 * inquiry - performs search of bluetooth devices
 *
 */
void inquiry (Hci* bdev) {

	bdev->num_rsp = hci_inquiry(bdev->id, LEN, MAX_LEN, NULL, &bdev->inq_info, IREQ_CACHE_FLUSH);
}
