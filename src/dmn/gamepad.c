#include "ds4linux.h"

/*
 * newGamepad - object constructor
 *
 * return: Object struct pointer
 */
Gamepad* newGamepad(void) {

	printf("Allocating gamepad\n");
	Gamepad* newgamepad = malloc(sizeof(Gamepad));

	if (newgamepad)
		initGamepad(newgamepad);

	return (newgamepad);
}

/*
 * initGamepad - object initializer
 *
 * @self: Object struct pointer
 */
void initGamepad(Gamepad* self) {

	printf("initializing gamepad\n");
	memset(self, 0, sizeof(Gamepad));
	self->connect = &connectGamepad;
	self->disconnect = &disconnectGamepad;
	self->send = &sendGamepad;
	self->recv = &recvGamepad;
	self->sockCTRL = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	self->sockITRP = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
}

/*
 * deleteGamepad - object destructor
 *
 * @self: Object struct pointer
 */
void deleteGamepad(Gamepad* self){

	printf("deleting gamepad\n");
	disconnectGamepad(self);
	free(self);
}

/*
 * connectGamepad - makes connection to gamepad
 *
 * @self: Object struct pointer
 * @bdaddr: bluetooth address of gamepad
 */
void connectGamepad (Gamepad* self, bdaddr_t bdaddr) {

	printf("connecting gamepad\n");
	struct sockaddr_l2 rem_sock;
	memset(&rem_sock, 0, sizeof(struct sockaddr_l2));
	rem_sock.l2_bdaddr = bdaddr;
	rem_sock.l2_family = AF_BLUETOOTH;
	rem_sock.l2_psm = htobs(HID_CTRL);
	
	connect(self->sockCTRL,\
		       	(struct sockaddr*)&rem_sock,\
		       	sizeof(struct sockaddr_l2));
	rem_sock.l2_psm = htobs(HID_ITRP);

	connect(self->sockITRP,\
                        (struct sockaddr*)&rem_sock,\
                        sizeof(struct sockaddr_l2));
	ba2str(&bdaddr, self->bdaddr);
}

/*
 * disconnectGamepad - removes connection from gamepad
 *
 * @self: Object struct pointer
 */
void disconnectGamepad(Gamepad* self) {

	printf("disconnecting gamepad\n");
	close(self->sockCTRL);
	close(self->sockITRP);
}

/*
 * sendGamepad - writes to gamepad
 *
 * @self: struct pointer
 */
void sendGamepad() {

}

/*
 * recvGamepad - read from gamepad
 *
 * @self: Object struct pointer
 */
void recvGamepad(Gamepad* self) {

	printf("Receiving input\n");	
	uint8_t buffer[11];
	recv(self->sockITRP, buffer, sizeof(buffer), 0);
	
	for(int i = 0; i < 11; i++){

		printf("%d: ", buffer[i]);
	}
	printf("\n");
}
