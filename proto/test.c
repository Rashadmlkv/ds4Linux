#include "dmn.h"

bd bdev;
int
main ( void) {

	//daemonize the process

start:

	//lower priority
	priority( 19);

	//wait until bluetooth turned on
	while ( hci_get_route( NULL) == -1);

	//increase priority
	priority( 0);

	//set bluetooth adapter
	setBluetoothAdapter();

	if ( !(bdev.inq_info))
		goto finish;

	//do stuff until bluetooth turned off
	do {

		//search devices
		searchDevices();
	        //check device is controller
		isController();
		//install module
	} while ( hci_get_route ( NULL) != -1);

	goto start;

finish:
	//cleanup
	
	return (errno);
}
