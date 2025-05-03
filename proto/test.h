#ifndef DMN_H
#define DMN_H

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>

#define MAX_RSP 255
#define LEN 8
#define CONTROLLER_CLASS 0x002508

typedef struct {

        inquiry_info * inq_info;
        short id, num_rsp;
} bd;
extern bd bdev;

int priority (uint8_t priority);
void setBluetoothAdapter ();
void searchDevices ();
void isController ();

#endif
