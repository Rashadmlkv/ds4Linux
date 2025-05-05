#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <bluetooth/l2cap.h>
#include <sys/socket.h>
#define HID_CTRL 0x11
#define HID_ITRP 0x13


typedef struct gamepad {

	struct gamepad* next;
	char bdaddrstr[18];
        int8_t (*connect)(struct gamepad* self, bdaddr_t bdaddr);
	void (*disconnect)(struct gamepad* self);
	bdaddr_t bdaddr;
	int8_t sockCTRL, sockITRP;
} Gamepad;

Gamepad* newGamepad(void);
int8_t connectGamepad (struct gamepad* self, bdaddr_t bdaddr);
void disconnectGamepad (struct gamepad* self);
#endif
