#ifndef DMN_H
#define DMN_H

#define MAX_RSP 255

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>

typedef struct {

        inquiry_info * inq_info;
        short id, num_rsp;
} bd;


#endif
