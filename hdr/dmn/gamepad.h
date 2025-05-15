#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <bluetooth/l2cap.h>

#define HID_CTRL 0x11
#define HID_ITRP 0x13

typedef struct gamepad {

	struct gamepad* next;
        char bdaddr[19];
        void (*connect)(struct gamepad* self, bdaddr_t bdaddr);
        void (*disconnect)(struct gamepad* self);
        void (*send)(struct gamepad* self);
        void (*recv)(struct gamepad* self);
        int sockCTRL, sockITRP;
} Gamepad;

Gamepad* newGamepad(void);
void initGamepad(Gamepad* self);
void deleteGamepad(Gamepad* self);
void connectGamepad (Gamepad* self, bdaddr_t bdaddr);
void disconnectGamepad(Gamepad* self);
void sendGamepad();
void recvGamepad();

#endif
