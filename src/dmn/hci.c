#include "dmn.h"


int priority (uint8_t priority) {

    errno = 0;
    
    if ( nice( priority) == -1 && errno != 0) {

            perror( "");
    }
    return (errno);
}
void setBluetoothAdapter () {

        bdev.id = hci_get_route( NULL);
        bdev.num_rsp = 0;
        bdev.inq_info = malloc( MAX_RSP * sizeof( inquiry_info));

        if ( !(bdev.inq_info)) {

                perror ( "");
        }
}

void searchDevices () {

        bdev.num_rsp = hci_inquiry( bdev.id, LEN, MAX_RSP, NULL, &bdev.inq_info, IREQ_CACHE_FLUSH);

        if ( bdev.num_rsp == -1)
                perror( "");
}

void isController () {

	uint32_t dev_class = 0;
        int i;
        for ( i = 0; i < bdev.num_rsp; i++) {

                dev_class = ( (bdev.inq_info + i)->dev_class[2] << 16)|\
                            ( (bdev.inq_info + i)->dev_class[1] << 8)|\
                            ( (bdev.inq_info + i)->dev_class[0]);

                if ( dev_class == CONTROLLER_CLASS)
			continue;
                        //add to list if new
        }
}
