#include "dmn.h"

bluetooth_device bdev;
gamepad_list * gamepads;
struct sockaddr_l2 gamepad_sock;

int
main (void) {

	gamepad_sock.l2_family = AF_BLUETOOTH;

mainloop:
	

	while ( hci_get_route( NULL) == -1);
	
	initBluetoothDevice();

	do {

		gamepadConnect();
	} while ( hci_get_route( NULL) != -1);

	goto mainloop;

//quit:
	return 0;
}


void initBluetoothDevice () {

	bdev.id = hci_get_route( NULL);
	bdev.num_rsp = 0;
	bdev.inq_info = malloc( MAX_RSP * sizeof( inquiry_info));

	if ( !(bdev.inq_info))
		printf ("PLACEHOLDER REMOVE ME , I will raise sig\n");
}
