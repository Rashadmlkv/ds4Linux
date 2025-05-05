#include "dmn.h"


/*
 * newGamepad - allocates memory for new Gamepad object
 *
 * return: newly allocated memory address
 */
Gamepad* newGamepad(void) {

	Gamepad* newgamepad = malloc(sizeof(Gamepad));
	
	newgamepad->next = NULL;
	memset(&newgamepad->bdaddrstr, 0, sizeof(newgamepad->bdaddrstr));
	newgamepad->connect = &connectGamepad;
	newgamepad->disconnect = &disconnectGamepad;
	memset(&newgamepad->bdaddr, 0, sizeof(newgamepad->bdaddr));
	newgamepad->sockCTRL = newgamepad->sockITRP = 0;
	return (newgamepad);
}

/*
 * connectGamepad - connects to gamepad
 *
 * @self: a gamepad object
 * @bdaddr: bluetooth address of gamepad
 *
 * return: 0 on succesfull connection, -1 on error
 */
int8_t connectGamepad (struct gamepad* self, bdaddr_t bdaddr) {

	self->bdaddr = bdaddr;
	ba2str(&self->bdaddr, self->bdaddrstr);
	struct sockaddr_l2 rem_sock;
	memset(&rem_sock, 0, sizeof(rem_sock));
	errno = 0;

	self->sockCTRL = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
        self->sockITRP = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	
	rem_sock.l2_family = AF_BLUETOOTH;
	rem_sock.l2_bdaddr = self->bdaddr;

	rem_sock.l2_psm = htobs(HID_CTRL);
	connect(self->sockCTRL, (struct sockaddr *) &rem_sock, sizeof(rem_sock));
	
	rem_sock.l2_psm = htobs(HID_ITRP);
	connect(self->sockITRP, (struct sockaddr *) &rem_sock, sizeof(rem_sock));
	perror("");	
	if (errno != 0)
		return (-1);
	else
		return (0);
}

/*
 * disconnectGamepad - closes connection to gamepad
 * 
 * @self: a gamepad object
 */
void disconnectGamepad (struct gamepad* self) {

//in case socket() failed
	close(self->sockCTRL);
	close(self->sockITRP);
}
