#ifndef DMN_H
#define DMN_H

#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>

#define LEN 8
#define MAX_RSP 127
#define GAMEPAD_CLASS 0x002508
#define HCI_CTRL 0x11
#define HCI_ITRP 0x13

typedef struct {

	int8_t id, num_rsp;
	inquiry_info * inq_info;
} bluetooth_device;

typedef struct node {

	struct node * next;
	char * bdaddr;;
	int8_t sockCTRL, sockITRP;
} gamepad_list;

extern bluetooth_device bdev;
extern gamepad_list * gamepads;
extern struct sockaddr_l2 gamepad_sock;

void initBluetoothDevice();
void gamepadConnect();
int8_t gamepadsAppend (uint8_t i);
int8_t tryConnect (gamepad_list * node, uint8_t i);
#endif
