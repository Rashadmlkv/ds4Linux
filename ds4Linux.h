#ifndef DS_4_LINUX
#define DS_4_LINUX

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

//controller 
#define CLS_DEV 0x002508
#define HID_CTRL 0x11
#define HID_ITRP 0x13

//search 
#define MAX_RSP 255
#define LEN 8


//controller info
typedef struct {

	struct sockaddr_l2 sock;
	uint8_t portCTRL, portITRP;
} ds4;

//list of found devices
typedef struct node {

	ds4 controller;
	struct node* next;
} controller_list;

extern controller_list* head;

int addController (bdaddr_t addr);
int connectController ();
void freeControllerList ();
int readControllerInput ();
#endif
